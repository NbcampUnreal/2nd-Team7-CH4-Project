


#include "Player/UMUMenuController.h"

#include "Managers/UMUMenuGameState.h"
#include "Widget/HUDMenu.h"
#include "UMUSmash/UMUSmash.h"
#include "InputCoreTypes.h"

void AUMUMenuController::BlockClientInput()
{
	if (!HasAuthority())
	{
		SetInputMode(FInputModeGameOnly());
	}
}

void AUMUMenuController::SetUseCursor(const bool& bUseCursor)
{
	bShowMouseCursor = bUseCursor;
	bEnableClickEvents = bUseCursor;
	bEnableMouseOverEvents = bUseCursor;

}

void AUMUMenuController::ChangeNextProgressUI(EMenuWidgetState NextWidgetState)
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	check(HUDMenuInstance)

	HUDMenuInstance->UpdateUIToProgress(NextWidgetState);

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuController::BeginPlay()
{
	Super::BeginPlay();

	AddHUDWidget();
	SetUseCursor(true);
	SetInputMode(FInputModeGameOnly());
	
}

void AUMUMenuController::AddHUDWidget()
{
	check(HUDMenuClass);
	
	if (IsLocalController())
	{
		HUDMenuInstance = CreateWidget<UHUDMenu>(this, HUDMenuClass);
		if (HUDMenuInstance)
		{
			HUDMenuInstance->AddToViewport();
		}
		else
		{
			UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("HUDMenuInstance is null"));
		}
	}
}
