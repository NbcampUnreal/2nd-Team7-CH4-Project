


#include "Player/UMUMenuController.h"

#include "Managers/UMUMenuGameState.h"
#include "Widget/HUDMenu.h"
#include "Widget/HUDLobby.h"
#include "UMUSmash/UMUSmash.h"
#include "InputCoreTypes.h"
#include "Net/UnrealNetwork.h"
#include "Widget/CharacterSelectWidget.h"

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
	check(HUDMenuInstance)

	HUDMenuInstance->UpdateUIToProgress(NextWidgetState);
}

void AUMUMenuController::UpdateCPUCount(const int32& NewValue)
{
	if (GetNetMode() == NM_Standalone)
	{
		HUDMenuInstance->GetCharacterSelectWidget()->UpdateCPUCount(NewValue);
	}
	else
	{
		HUDLobbyInstance->GetCharacterSelectWidget()->UpdateCPUCount(NewValue);
	}
}

void AUMUMenuController::UpdateCPUMaxCount(const int32& NewValue)
{
	if (GetNetMode() == NM_Standalone)
	{
		HUDMenuInstance->GetCharacterSelectWidget()->UpdateCPUMaxCount(NewValue);
	}
	else
	{
		HUDLobbyInstance->GetCharacterSelectWidget()->UpdateCPUMaxCount(NewValue);
	}
}

void AUMUMenuController::UpdateRuleCount(const int32& NewValue)
{
	if (GetNetMode() == NM_Standalone)
	{
		HUDMenuInstance->GetCharacterSelectWidget()->UpdateRuleCount(NewValue);
	}
	else
	{
		HUDLobbyInstance->GetCharacterSelectWidget()->UpdateRuleCount(NewValue);
	}
}

void AUMUMenuController::UpdateInGameMode(const EInGameModes NewInGameMode)
{
	if (GetNetMode() == NM_Standalone)
	{
		HUDMenuInstance->GetCharacterSelectWidget()->UpdateInGameMode(NewInGameMode);
	}
	else
	{
		HUDLobbyInstance->GetCharacterSelectWidget()->UpdateInGameMode(NewInGameMode);
	}
}


void AUMUMenuController::ServerRPCSetCPUCount_Implementation(const int32& NewCount)
{
	
	auto* CurrentGameState = GetWorld()->GetGameState<AUMUMenuGameState>();
	if (CurrentGameState)
	{
		CurrentGameState->SetCPUCount(NewCount);
	}

}

void AUMUMenuController::ServerRPCSetRuleCount_Implementation(const int32& NewCount)
{
	auto* CurrentGameState = GetWorld()->GetGameState<AUMUMenuGameState>();
	if (CurrentGameState)
	{
		CurrentGameState->SetRuleCount(NewCount);
	}
}

void AUMUMenuController::ServerRPCChangeRule_Implementation(const EInGameModes& NewInGameMode)
{
	auto* CurrentGameState = GetWorld()->GetGameState<AUMUMenuGameState>();
	if (CurrentGameState)
	{
		CurrentGameState->ChangeRule(NewInGameMode);
	}
}


void AUMUMenuController::ServerRPCSelectedCharacter_Implementation(const ECharacter& SelectedCharacterValue)
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))

	if (bIsReady)
	{
		if (SelectedCharacterValue != SelectedCharacter)
		{
			return;
		}
	}
	
	bIsReady = !bIsReady;
	SelectedCharacter = SelectedCharacterValue;
	
	auto* CurrentGameState = GetWorld()->GetGameState<AUMUMenuGameState>();
	if (CurrentGameState)
	{
		if (bIsReady)
		{
			CurrentGameState->SetPlayerCharactersArray(PlayerID, SelectedCharacter);
		}
		CurrentGameState->SetPlayerReadyArray(PlayerID, bIsReady);
	}
	
	OnRep_IsReady();


	const UEnum* EnumPtr = StaticEnum<ECharacter>();
	if (EnumPtr)
	{
		const FString EnumToString = EnumPtr->GetNameStringByValue(static_cast<uint8>(SelectedCharacterValue));
		if (bIsReady)
		{
			UMU_LOG(LogUMU, Log, TEXT("bIsReady:true, PlayerID:%d, ECharacter:%s"), PlayerID, *EnumToString)
		}
		else
		{
			UMU_LOG(LogUMU, Log, TEXT("bIsReady:false, PlayerID:%d, ECharacter:%s"), PlayerID, *EnumToString)
		}
	}
	
	
	
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuController::BeginPlay()
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	Super::BeginPlay();

	AddHUDWidget();
	SetUseCursor(true);
	SetInputMode(FInputModeUIOnly());

	if (HasAuthority())
	{
		AddNumberOfPlayers();	
	}
	
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuController::AddNumberOfPlayers()
{
	auto* CurrentGameState = GetWorld()->GetGameState<AUMUMenuGameState>();
	if (CurrentGameState)
	{
		PlayerID = CurrentGameState->GetNumberOfPlayers();
		const int32 NewCount = PlayerID + 1;
		CurrentGameState->SetNumberOfPlayers(NewCount);
		
		UMU_LOG(LogUMU, Log, TEXT("PlayerID:%d"), PlayerID)
	}
}

void AUMUMenuController::OnRep_IsReady()
{
	
}

void AUMUMenuController::AddHUDMenu()
{
	if (IsLocalController())
	{
		HUDMenuInstance = CreateWidget<UHUDMenu>(this, HUDMenuClass);
		if (HUDMenuInstance)
		{
			HUDMenuInstance->AddToViewport();
			HUDMenuInstance->InitWidget();
		}
		else
		{
			UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("HUDMenuInstance is null"));
		}
	}
}

void AUMUMenuController::AddHUDLobby()
{
	if (IsLocalController())
	{
		HUDLobbyInstance = CreateWidget<UHUDLobby>(this, HUDLobbyClass);
		if (HUDLobbyInstance)
		{
			HUDLobbyInstance->AddToViewport();
			HUDLobbyInstance->InitWidget();
		}
		else
		{
			UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("HUDLobbyInstance is null"));
		}
	}
}

void AUMUMenuController::AddHUDWidget()
{
	check(HUDMenuClass);

	if (GetWorld())
	{
		auto* CurrentGameState = GetWorld()->GetGameState<AUMUMenuGameState>();
		if (CurrentGameState)
		{
			bool IsOnlineMode = CurrentGameState->GetIsOnlineMode();
			if (IsOnlineMode)
			{
				AddHUDLobby();
			}
			else
			{
				AddHUDMenu();
			}
		}
	}
}

void AUMUMenuController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUMUMenuController, PlayerID);
	DOREPLIFETIME(AUMUMenuController, bIsReady);
}
