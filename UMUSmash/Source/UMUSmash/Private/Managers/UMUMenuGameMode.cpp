
#include "Managers/UMUMenuGameMode.h"
#include "Managers/UMUGameInstance.h"
#include "Managers/UMUMenuGameState.h"
#include "Player/UMUMenuController.h"

AUMUMenuGameMode::AUMUMenuGameMode()
{
	
}

void AUMUMenuGameMode::SetIsOnlineMode() const
{
	if (GetWorld())
	{
		auto* CurrentGameMode = GetWorld()->GetGameState<AUMUMenuGameState>();
		if (CurrentGameMode)
		{
			CurrentGameMode->SetIsOnlineMode(false);
		}
	}
}


void AUMUMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetIsOnlineMode();
}

void AUMUMenuGameMode::ServerTravelToNextMap()
{
	const UEnum* MapPtr = StaticEnum<EMaps>();
	check(MapPtr);
	
	const int64 NextMapToInt64 = static_cast<int64>(NextMap);
	const FString MapNameToString = MapPtr->GetNameStringByValue(NextMapToInt64);

	if (GetWorld())
	{
		GetWorld()->ServerTravel(MapNameToString);	
	}
}

void AUMUMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (bBlockAddClient)
	{
		NewPlayer->SetLifeSpan(0.1f);
	}
	
	bBlockAddClient = true;	
}
