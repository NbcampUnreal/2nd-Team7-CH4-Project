


#include "Managers/UMULobbyGameMode.h"

#include "Managers/UMUMenuGameState.h"

void AUMULobbyGameMode::SetIsOnlineMode() const
{
	if (GetWorld())
	{
		auto* CurrentGameMode = GetWorld()->GetGameState<AUMUMenuGameState>();
		if (CurrentGameMode)
		{
			CurrentGameMode->SetIsOnlineMode(true);
		}
	}
	
}


void AUMULobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetIsOnlineMode();
}
