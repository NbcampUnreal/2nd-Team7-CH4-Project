#include "Character/UMUPlayerController.h"
#include "EnhancedInputSubsystems.h"

AUMUPlayerController::AUMUPlayerController()
{

}

void AUMUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
