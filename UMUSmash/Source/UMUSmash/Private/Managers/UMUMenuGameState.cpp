


#include "Managers/UMUMenuGameState.h"

#include "Net/UnrealNetwork.h"
#include "Player/UMUMenuController.h"
#include "UMUSmash/UMUSmash.h"
#include "Widget/HUDLobby.h"
#include "Widget/HUDMenu.h"


void AUMUMenuGameState::CheckAllPlayerReady()
{
	if (ReadyArray.Num() <= 1)
	{
		return;
	}

	if (ReadyArray.Contains(false))
	{
		return;
	}

	auto* CurrentPlayerController = GetWorld()->GetFirstPlayerController();
	if (CurrentPlayerController)
	{
		auto* MenuController = Cast<AUMUMenuController>(CurrentPlayerController);
		if (MenuController)
		{
			if (GetNetMode() == NM_Standalone)
			{
				MenuController->GetHUDMenuInstance()->UpdateUIToProgress(EMenuWidgetState::MapSelect);
			}
			else
			{
				MenuController->GetHUDLobbyInstance()->UpdateUIToProgress(EMenuWidgetState::MapSelect);
			}
		}
	}
}

void AUMUMenuGameState::SetNumberOfPlayers(const int& NewValue)
{
	NumberOfPlayers = NewValue;

	CheckCPUArray();
	UMU_LOG(LogUMU, Log, TEXT("NumberOfPlayers:%d"), NumberOfPlayers)
}

void AUMUMenuGameState::SetCPUCount(const int32& NewValue)
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	const int32 NewCount = FMath::Clamp(NewValue, 0, 4 - NumberOfPlayers);
	CPUCount = NewCount;
	OnRep_CPUCount();

	CheckCPUArray();

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuGameState::SetRuleCount(const int32& NewValue)
{
	if (InGameMode == EInGameModes::Stock)
	{
		StockCount = NewValue;
		OnRep_StockCount();
	}
	if (InGameMode == EInGameModes::Time)
	{
		Minutes = NewValue;
		OnRep_Minutes();
	}
}

void AUMUMenuGameState::SetPlayerCharactersArray(const int32& PlayerID, const ECharacter& SelectedCharacter)
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	if (PlayerCharacters.Num() < PlayerID+1)
	{
		PlayerCharacters.SetNum(PlayerID+1);
	}
	PlayerCharacters[PlayerID] = SelectedCharacter;

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuGameState::SetPlayerReadyArray(const int32& PlayerID, const bool& bIsReady)
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	if (ReadyArray.Num() < PlayerID+1)
	{
		ReadyArray.SetNum(PlayerID+1);
	}
	ReadyArray[PlayerID] = bIsReady;
	
	CheckAllPlayerReady();

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuGameState::CheckCPUArray()
{
	const int32 TotalPlayerCount = NumberOfPlayers + CPUCount;

	if (CPUCheckArray.Num() < TotalPlayerCount)
	{
		CPUCheckArray.SetNum(TotalPlayerCount);
	}

	for (int32 i = 0; i < TotalPlayerCount; i++ )
	{
		if (i <= NumberOfPlayers)
		{
			CPUCheckArray[i] = false;
			continue;
		}
		CPUCheckArray[i] = true;
	}
}

void AUMUMenuGameState::ChangeRule(const EInGameModes& NewInGameMode)
{
	if (NewInGameMode == EInGameModes::Stock)
	{
		InGameMode = EInGameModes::Time;
	}
	if (NewInGameMode == EInGameModes::Time)
	{
		InGameMode = EInGameModes::Stock;
	}

	OnRep_InGameMode();
}

void AUMUMenuGameState::OnRep_IsOnlineMode()
{

}

void AUMUMenuGameState::OnRep_NumberOfPlayers()
{
	
}

void AUMUMenuGameState::OnRep_CPUCount() const
{
	auto* LocalController = GetWorld()->GetFirstPlayerController();
	if (LocalController)
	{
		auto* MenuController = Cast<AUMUMenuController>(LocalController);
		if (MenuController)
		{
			const int32 CPUMaxCount = 4 - NumberOfPlayers;
			MenuController->UpdateCPUCount(CPUCount);
			MenuController->UpdateCPUMaxCount(CPUMaxCount);
		}
	}
}

void AUMUMenuGameState::OnRep_InGameMode()
{
	auto* LocalController = GetWorld()->GetFirstPlayerController();
	if (LocalController)
	{
		auto* MenuController = Cast<AUMUMenuController>(LocalController);
		if (MenuController)
		{
			MenuController->UpdateInGameMode(InGameMode);
		}
	}
}

void AUMUMenuGameState::OnRep_StockCount()
{
	auto* LocalController = GetWorld()->GetFirstPlayerController();
	if (LocalController)
	{
		auto* MenuController = Cast<AUMUMenuController>(LocalController);
		if (MenuController)
		{
			MenuController->UpdateRuleCount(StockCount);
		}
	}
}

void AUMUMenuGameState::OnRep_Minutes()
{
	auto* LocalController = GetWorld()->GetFirstPlayerController();
	if (LocalController)
	{
		auto* MenuController = Cast<AUMUMenuController>(LocalController);
		if (MenuController)
		{
			MenuController->UpdateRuleCount(Minutes);
		}
	}
}

void AUMUMenuGameState::BeginPlay()
{
	Super::BeginPlay();

	// BeginPlay = Changed Map
	if (HasAuthority())
	{
		SetNumberOfPlayers(0);
	}
}

void AUMUMenuGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUMUMenuGameState, bIsOnlineMode);
	DOREPLIFETIME(AUMUMenuGameState, NumberOfPlayers);
	DOREPLIFETIME(AUMUMenuGameState, CPUCount);
	DOREPLIFETIME(AUMUMenuGameState, InGameMode);
	DOREPLIFETIME(AUMUMenuGameState, Minutes);
	DOREPLIFETIME(AUMUMenuGameState, StockCount);
}
