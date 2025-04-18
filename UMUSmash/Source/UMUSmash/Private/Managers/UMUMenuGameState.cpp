


#include "Managers/UMUMenuGameState.h"

#include "Managers/UMUGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Player/UMUMenuController.h"
#include "UMUSmash/UMUSmash.h"


void AUMUMenuGameState::CheckAllPlayerReady()
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	if (ReadyArray.Num() <= 1)
	{
		return;
	}

	if (ReadyArray.Contains(false))
	{
		return;
	}
	
	SaveGameData();	
	// RandomMapTravel();

	bAllPlayersReady = true;

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuGameState::SetNumberOfPlayers(const int& NewValue)
{
	NumberOfPlayers = NewValue;
	TotalPlayerCount = NumberOfPlayers + CPUCount;
	FitToSizeArray();
	CheckCPUArray();
	
	UMU_LOG(LogUMU, Log, TEXT("NumberOfPlayers:%d"), NumberOfPlayers)
}

void AUMUMenuGameState::SetCPUCount(const int32& NewValue)
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	const int32 NewCount = FMath::Clamp(NewValue, 0, 4 - NumberOfPlayers);
	CPUCount = NewCount;
	TotalPlayerCount = NumberOfPlayers + CPUCount;
	OnRep_CPUCount();
	
	FitToSizeArray();
	CheckCPUArray();

	UMU_LOG(LogUMU, Log, TEXT("TotalPlayerCount:%d NumberOfPlayerCount:%d CPUCount:%d"), TotalPlayerCount, NumberOfPlayers, CPUCount)
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
	
	ReadyArray[PlayerID] = bIsReady;
	
	CheckAllPlayerReady();

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuGameState::CheckCPUArray()
{
	TotalPlayerCount = NumberOfPlayers + CPUCount;
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

void AUMUMenuGameState::DoCPUReady()
{
	for (int32 i = 0; i < TotalPlayerCount - 1; i++)
	{
		ReadyArray[(TotalPlayerCount-1)-i] = false;
	}

	for (int32 i = 0; i < CPUCount; i++)
	{
		ReadyArray[(TotalPlayerCount-1)-i] = true;
	}
}

void AUMUMenuGameState::SelectCPUCharacter()
{
	const uint8 RandomCharacterIndex = FMath::RandRange(1,12);
	ECharacter RandomCharacter;

#pragma region RandomCharacter
	switch (RandomCharacterIndex)
	{
	case 1:
		{
			RandomCharacter = ECharacter::Unity_Dog;
			break;
		}
	case 2:
		{
			RandomCharacter = ECharacter::Unity_TinyHeroBoy;
			break;
		}
	case 3:
		{
			RandomCharacter = ECharacter::Unity_TinyHeroGirl;
			break;
		}
	case 4:
		{
			RandomCharacter = ECharacter::Unity_Hero;
			break;
		}
	case 5:
		{
			RandomCharacter = ECharacter::Unreal_Rampage;
			break;
		}
	case 6:
		{
			RandomCharacter = ECharacter::Unreal_Crunch;
			break;
		}
	case 7:
		{
			RandomCharacter = ECharacter::Unreal_Gideon;
			break;
		}
	case 8:
		{
			RandomCharacter = ECharacter::Unreal_Kallari;
			break;
		}
	case 9:
		{
			RandomCharacter = ECharacter::Mixamo_XBot;
			break;
		}
	case 10:
		{
			RandomCharacter = ECharacter::Mixamo_YBot;
			break;
		}
	case 11:
		{
			RandomCharacter = ECharacter::Mixamo_Swat;
			break;
		}
	case 12:
		{
			RandomCharacter = ECharacter::Mixamo_Michelle;
			break;
		}
	default:
		{
			RandomCharacter = ECharacter::Unity_Dog;
			break;
		}
	}
#pragma endregion
	if (CPUCount != 0)
	{
		PlayerCharacters[TotalPlayerCount-CPUCount] = RandomCharacter;	
	}
}

FString AUMUMenuGameState::RandomMapSelect() const 
{
	TArray<FString> MapArray = {TEXT("Concluding_Ground"), TEXT("ConflictZone"), TEXT("IceZone"), TEXT("BattlePlace"), TEXT("TheWalkWay")}; 

	const int32 RandomMapIndex = FMath::RandRange(0,4);
	
	return MapArray[RandomMapIndex];
}

void AUMUMenuGameState::SaveGameData() const
{
	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
	
	auto* CurrentGameInstance = Cast<UUMUGameInstance>(GetGameInstance());
	if (CurrentGameInstance)
	{
		CurrentGameInstance->SetCPU(CPUCheckArray);
		CurrentGameInstance->SetStockCount(StockCount);
		CurrentGameInstance->SetMin(Minutes);
		CurrentGameInstance->SetSubGameMode(InGameMode);
		CurrentGameInstance->SetNumberOfPlayers(NumberOfPlayers);
		CurrentGameInstance->SetPlayerCharacters(PlayerCharacters);
		CurrentGameInstance->SetIsOnline(bIsOnlineMode);

		UMU_LOG(LogUMU, Log, TEXT("InstanceData, StockCount:%d Minutes:%d NumberOfPlayers:%d"), StockCount, Minutes, NumberOfPlayers)
	}

	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
}

void AUMUMenuGameState::FitToSizeArray()
{
	TotalPlayerCount = NumberOfPlayers + CPUCount;

	if (PlayerCharacters.Num() < TotalPlayerCount)
	{
		PlayerCharacters.SetNum(TotalPlayerCount);
	}
	
	if (ReadyArray.Num() < TotalPlayerCount)
	{
		ReadyArray.SetNum(TotalPlayerCount);
	}

	if (CPUCheckArray.Num() < TotalPlayerCount)
	{
		CPUCheckArray.SetNum(TotalPlayerCount);
	}
}

// void AUMUMenuGameState::RandomMapTravel() const
// {
// 	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("Begin"))
// 	
// 	EMaps RandomMap = RandomMapSelect();
// 	FString NextMapToString;
// 	const UEnum* EnumPtr = StaticEnum<EMaps>();
// 	if (EnumPtr)
// 	{
// 		NextMapToString = EnumPtr->GetNameStringByIndex(static_cast<uint8>(RandomMap));
// 	}
// 	else
// 	{
// 		UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("EnumPtr is null"))
// 	}
// 	
// 	UMU_LOG(LogUMU, Log, TEXT("NextMapName:%s"), *NextMapToString)
// 			
// 	if (GetNetMode() == NM_Standalone)
// 	{
// 		const FName NextMapToName = FName(*NextMapToString);
// 		UGameplayStatics::OpenLevel(GetWorld(), NextMapToName);
// 	}
// 	else
// 	{
// 		GetWorld()->ServerTravel(NextMapToString, true);
// 	}
// 	
// 	UMU_LOG(LogUMU, Log, TEXT("%s"), TEXT("End"))
// }

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

	if (GetNetMode() != NM_Standalone)
	{
		bIsOnlineMode = true;
	}
	else
	{
		bIsOnlineMode = false;
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
