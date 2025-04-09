


#include "Managers/UMUGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/UMUGameInstance.h"

void AUMUGameState::MulticastRPCIsGameOver_Implementation()
{
	SlowMotionEffect();
}

void AUMUGameState::SlowMotionEffect()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);

	FTimerHandle FinalGameStatsHandle;
	GetWorld()->GetTimerManager().SetTimer(
		FinalGameStatsHandle,FTimerDelegate::CreateLambda([this]
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		}),
		0.2f,false, -1);
}

void AUMUGameState::UpdateIsGameOver()
{
	bIsGameOver = GameInstance->IsGameOver();
}
