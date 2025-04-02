#include "Character/UMUPlayerController.h"
#include "EnhancedInputSubsystems.h"
AUMUPlayerController::AUMUPlayerController()
{

}

void AUMUPlayerController::BeginPlay()
{
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}
