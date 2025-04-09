


#include "Managers/UMUGameInstance.h"

#include "Managers/UMUFightGameMode.h"
#include "Managers/UMUGameState.h"
#include "UMUSmash/UMUSmash.h"

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

void UUMUGameInstance::CheckGameOverConditions()
{
	auto* FighterGameMode = Cast<AUMUFightGameMode>(GetWorld()->GetAuthGameMode());
	checkf(FighterGameMode, TEXT("Game Instance: Fighter Game Mode is null"));

	FighterGameMode->CheckGameOverConditions();
}
