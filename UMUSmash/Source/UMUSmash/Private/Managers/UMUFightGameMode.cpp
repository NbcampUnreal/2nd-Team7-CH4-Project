


#include "Managers/UMUFightGameMode.h"
#include "Managers/UMUGameInstance.h"
#include "Managers/UMUGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UMUSmash/UMUSmash.h"




void AUMUFightGameMode::CreatePlayers()
{
	check(GameInstance);

	const int32 CashedNumberOfPlayers = GameInstance->GetNumberOfPlayers();
	NumberOfPlayers = CashedNumberOfPlayers;

	if (!GameInstance->IsOnline())
	{
		return;
	}

	TArray<ECharacter> LoadedPlayers = GameInstance->GetPlayerCharacters();
	
	for (int32 i = 0; i < LoadedPlayers.Num(); i++)
	{
		if (LoadedPlayers[i] != ECharacter::None)
		{
			auto* PlayerController = UGameplayStatics::CreatePlayer(GetWorld(), i, true);
			// 콘솔용 Play Dynamic Force Feedback 미구현, 구현 시 PlayerController 사용
			
			Stocks[i] = GameInstance->GetStockCount();
		}
	}
	
	Minutes = GameInstance->GetMin();
}

bool AUMUFightGameMode::OnlineAllLoaded()
{
	checkf(GameInstance, TEXT("Fight Game Mode, OnlineAllLoaded : Game Instance is null"));
	
	ensure (GameInstance->GetNumberOfPlayers() == NumberOfPlayers);
	PlayerLoaded.SetNum(NumberOfPlayers);

	for (int32 i = 0; i < NumberOfPlayers; i++)
	{
		PlayerLoaded[i] = true;
	}

	return !PlayerLoaded.Contains(false);
}

void AUMUFightGameMode::MatchStats()
{
	const int32 AlivePlayerCount = NumberOfPlayers;
	NumPlayersAlive = AlivePlayerCount;
}

void AUMUFightGameMode::SetPlayerStocks()
{
	if (InGameMode == EInGameModes::Stock)
	{
		const int32 NoPlayers = NumberOfPlayers;
		Stocks.SetNum(NoPlayers);
		
		for (int32 i = 0; i < NoPlayers; i++)
		{
			Stocks[i] = GameInstance->GetStockCount();
		}
	}
}


void AUMUFightGameMode::HandleInitGame()
{
	GameInstance = Cast<UUMUGameInstance> (GetWorld()->GetGameInstance());
	check(GameInstance);

	CreatePlayers();
	OnlineAllLoaded();
	MatchStats();
	
	bUseTimer = (InGameMode == EInGameModes::Time);
	
}


void AUMUFightGameMode::FinalizeGameStats() const
{
	GameInstance->SetElims(Elims);
	GameInstance->SetFalls(Falls);
	GameInstance->SetDamageDone(DamageDone);
	GameInstance->SetDamageTaken(DamageTaken);
}

void AUMUFightGameMode::TravelToVictoryScreen() const
{
	const FString MapName = TEXT("VictoryScreen");
	
	if (GameInstance->IsOnline())
	{
		GameInstance->ServerTravel(MapName);	
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
	}
}

void AUMUFightGameMode::HandleGameOver() const
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"));
	
	check(GameInstance);
	
	auto* UMUGameState = GetWorld()->GetGameState<AUMUGameState>();
	check(UMUGameState);
	
	GameInstance->SetIsGameOver(true);
	UMUGameState->MulticastRPCIsGameOver();
	FinalizeGameStats();
	
	FTimerHandle FinalGameStatsHandle;
	GetWorld()->GetTimerManager().SetTimer(
		FinalGameStatsHandle,FTimerDelegate::CreateLambda([this]
		{
			TravelToVictoryScreen();
		}),
		3.0f,false, -1);

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"));
}

void AUMUFightGameMode::CheckGameOverConditions()
{
	UMU_LOG(LogUMU, Log, TEXT("%s : AliveCount %d, Minutes %d %s"), *FString("InGameMode"), NumPlayersAlive, Minutes, TEXT("Begin"));
	
	switch (InGameMode)
	{
		case EInGameModes::Stock:
			{
				if (NumPlayersAlive == 1)
				{
					HandleGameOver();
					break;
				}
			}
		case EInGameModes::Time:
			{
				if (Minutes < 0)
				{
					bUseTimer = false;
					HandleGameOver();
					break;
				}
			}
		case EInGameModes::MiniGame:
			{
				if (Minutes < 0)
				{
					bUseTimer = false;
					HandleGameOver();
					break;
				}
			}
		default:
			{
				break;
			}
	}

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"));
}


void AUMUFightGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleInitGame();
}
