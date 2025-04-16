#include "Managers/UMUGameInstance.h"
#include "Managers/UMUFightGameMode.h"
#include "Managers/UMUGameState.h"

void UUMUGameInstance::ServerTravel(const FString& MapName) const
{
	GetWorld()->ServerTravel(MapName);
}

bool UUMUGameInstance::IsGameOver() const
{
	return bIsGameOver;
}

void UUMUGameInstance::SetIsGameOver(const bool& NewValue)
{
	bIsGameOver = NewValue;
	GetWorld()->GetGameState<AUMUGameState>()->UpdateIsGameOver();
}

void UUMUGameInstance::CheckGameOverConditions() const
{
	auto* FighterGameMode = Cast<AUMUFightGameMode>(GetWorld()->GetAuthGameMode());
	checkf(FighterGameMode, TEXT("Game Instance: Fighter Game Mode is null"));

	FighterGameMode->CheckGameOverConditions();
}

void UUMUGameInstance::BroadcastChangedAliveCount() const
{
	const int32 ChangedValue = GetNumPlayersAlive();
	OnAliveCountChanged.Broadcast(ChangedValue);
}
