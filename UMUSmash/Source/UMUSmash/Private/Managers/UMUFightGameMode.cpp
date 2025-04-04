


#include "Managers/UMUFightGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/UMUGameInstance.h"



void AUMUFightGameMode::CreatePlayers()
{
	check(Instance);

	const int32 CashedNumberOfPlayers = Instance->GetNumberOfPlayers();
	NumberOfPlayers = CashedNumberOfPlayers;

	if (!Instance->IsOnline())
	{
		return;
	}

	TArray<ECharacter> LoadedPlayers = Instance->GetPlayerCharacters();
	
	for (int32 i = 0; i < LoadedPlayers.Num(); i++)
	{
		if (LoadedPlayers[i] != ECharacter::None)
		{
			auto* PlayerController = UGameplayStatics::CreatePlayer(GetWorld(), i, true);
			// 콘솔용 Play Dynamic Force Feedback 미구현, 구현 시 PlayerController 사용
			
			Stocks[i] = Instance->GetStockCount();
		}
	}
	
	Minutes = Instance->GetMinutes();
}

bool AUMUFightGameMode::OnlineLoaded()
{
	check(Instance);
	
	ensure (Instance->GetNumberOfPlayers() == NumberOfPlayers);
	PlayerLoaded.SetNum(NumberOfPlayers);

	for (int32 i = 0; i < NumberOfPlayers; i++)
	{
		PlayerLoaded[i] = true;
	}

	return !PlayerLoaded.Contains(false);
}

void AUMUFightGameMode::MatchStats()
{
	const int32 AlivePlayerCount = GetNumberOfPlayers();
	NumPlayersAlive = AlivePlayerCount;
}

void AUMUFightGameMode::SetPlayerStocks()
{
	if (GetInGameMode() == EInGameModes::Stock)
	{
		const int32 NoPlayers = GetNumberOfPlayers();
		Stocks.SetNum(NoPlayers);
		
		for (int32 i = 0; i < NoPlayers; i++)
		{
			Stocks[i] = Instance->GetStockCount();
		}
	}
}

void AUMUFightGameMode::HandleInitGame()
{
	Instance = Cast<UUMUGameInstance> (GetWorld()->GetGameInstance());
	check(Instance);

	CreatePlayers();
	OnlineLoaded();
	MatchStats();
	
	bUseTimer = (GetInGameMode() == EInGameModes::Time);
	
}


void AUMUFightGameMode::FinalizeGameStats() const
{
	Instance->SetElims(Elims);
	Instance->SetFalls(Falls);
	Instance->SetDamageDone(DamageDone);
	Instance->SetDamageTaken(DamageTaken);
}

void AUMUFightGameMode::TravelToVictoryScreen() const
{
	const FString MapName = TEXT("VictoryScreen");
	
	if (Instance->IsOnline())
	{
		Instance->ServerTravel(MapName);	
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
	}
}

void AUMUFightGameMode::HandleGameOver() const
{
	check(Instance);
	Instance->SetIsGameOver(true);

	// SlowMotion 적용 후 데이터 처리
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);

	FTimerHandle FinalGameStatsHandle;

	GetWorld()->GetTimerManager().SetTimer(
		FinalGameStatsHandle,FTimerDelegate::CreateLambda([this]
		{
			FinalizeGameStats();
			TravelToVictoryScreen();
		}),
		2.0f,false);
}


void AUMUFightGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleInitGame();
}
