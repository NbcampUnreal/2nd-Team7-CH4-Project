


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

	bAllLoaded = !PlayerLoaded.Contains(false);
	return bAllLoaded;
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


void AUMUFightGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (bAllLoaded)
	{
		NewPlayer->SetLifeSpan(0.1f);
	}
}

void AUMUFightGameMode::HandleInitGame()
{
	GameInstance = Cast<UUMUGameInstance> (GetWorld()->GetGameInstance());
	check(GameInstance);

	CreatePlayers();
	OnlineAllLoaded();
	MatchStats();
	BindingValueChanged();
	
	bUseTimer = (InGameMode == EInGameModes::Time);
	
}


void AUMUFightGameMode::FinalizeGameStats() const
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	GameInstance->SetElims(Elims);
	GameInstance->SetFalls(Falls);
	GameInstance->SetDamageDone(DamageDone);
	GameInstance->SetDamageTaken(DamageTaken);

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
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

void AUMUFightGameMode::BindingValueChanged()
{
	UMU_LOG(LogUMU,Log, TEXT("%s"), TEXT("Begin"));
	
	GameInstance = Cast<UUMUGameInstance> (GetWorld()->GetGameInstance());
	check(GameInstance);

	GameInstance->OnAliveCountChanged.AddDynamic(this, &AUMUFightGameMode::HandleUpdateAliveCount);

	UMU_LOG(LogUMU,Log, TEXT("%s"), TEXT("End"));
}

void AUMUFightGameMode::HandleUpdateAliveCount(const int32 NewNumPlayersAlive)
{
	UMU_LOG(LogUMU,Log, TEXT("%s"), TEXT("Begin"));
	
	NumPlayersAlive = NewNumPlayersAlive;
	CheckGameOverConditions();

	UMU_LOG(LogUMU,Log, TEXT("%s"), TEXT("End"));
}


void AUMUFightGameMode::HandleGameOver()
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"));
	
	check(GameInstance);
	
	auto* UMUGameState = GetWorld()->GetGameState<AUMUGameState>();
	check(UMUGameState);
	
	GameInstance->SetIsGameOver(true);
	UMUGameState->MulticastRPCIsGameOver();
	FinalizeGameStats();

	TWeakObjectPtr<AUMUFightGameMode> WeakThisPtr(this);
	FTimerHandle FinalGameStatsHandle;
	GetWorld()->GetTimerManager().SetTimer(
		FinalGameStatsHandle,
		FTimerDelegate::CreateLambda([WeakThisPtr]()
		{
			if (WeakThisPtr.IsValid() && WeakThisPtr->GetWorld())
			{
				WeakThisPtr->TravelToVictoryScreen();
			}
		}),
		3.0f,
		false,
		-1
	);

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"));
}

void AUMUFightGameMode::CheckGameOverConditions()
{
	UMU_LOG(LogUMU, Log, TEXT("%s : AliveCount %d, Minutes %d %s"), *FString("InGameMode"), NumPlayersAlive, Minutes, TEXT("Begin"));
	
	switch (InGameMode)
	{
		case EInGameModes::Stock:
			{
				if (GameInstance->GetNumPlayersAlive() == 1)
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

void AUMUFightGameMode::OnPlayerDeath(const int32& PlayerNo)
{
	check(GameInstance);
	
	TArray<bool> AliveArray = GameInstance->GetAliveArray();
	AliveArray[PlayerNo] = false;
	
	GameInstance->GetPlayerPositions().Insert(PlayerNo, 0);
	const int32 NewAlivePlayerCount = GameInstance->GetNumPlayersAlive()-1;
	GameInstance->SetNumPlayersAlive(NewAlivePlayerCount);
	GameInstance->BroadcastChangedAliveCount();
}

void AUMUFightGameMode::SetWinner() const
{
	TArray<bool> AliveArray = GameInstance->GetAliveArray();
	for (int32 i = 0; i < AliveArray.Num(); i++)
	{
		if (AliveArray[i])
		{
			GameInstance->SetWinnerPlayerID(i);
			TArray<int32> PlayerPosition = GameInstance->GetPlayerPositions();
			PlayerPosition.Insert(0,i);
			PlayerPosition[0] = i;
			PlayerPosition.SetNum(PlayerPosition.Num());
		}
	}
}

void AUMUFightGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleInitGame();
}
