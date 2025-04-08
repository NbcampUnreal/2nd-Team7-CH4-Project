


#include "Managers/UMUGameState.h"

#include "Kismet/GameplayStatics.h"

void AUMUGameState::MulticastRPCSlowMotionEffect_Implementation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);
}
