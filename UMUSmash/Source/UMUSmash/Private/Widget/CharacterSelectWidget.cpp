


#include "Widget/CharacterSelectWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/UMUMenuGameState.h"
#include "Player/UMUMenuController.h"
#include "Widget/SelectedCharacterPanelWidget.h"

void UCharacterSelectWidget::RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ChangeNextProgressUI(WidgetState);
	}
}

void UCharacterSelectWidget::UpdateRuleCount(const int32& NewCount)
{
	if (CurrentInGameMode == EInGameModes::Stock)
	{
		StockCount = NewCount;
	}

	if (CurrentInGameMode == EInGameModes::Time)
	{
		Minutes = NewCount;
	}
	
	const FText NewText = FText::AsNumber(NewCount);
	RuleCount->SetText(NewText);
}

void UCharacterSelectWidget::UpdateCPUCount(const int32& NewCount) const
{
	const FText NewText = FText::AsNumber(NewCount);
	CPUCount->SetText(NewText);
}

void UCharacterSelectWidget::UpdateCPUMaxCount(const int32& NewCount)
{
	CPUMaxCount = NewCount;
}

void UCharacterSelectWidget::UpdateInGameMode(const EInGameModes& NewInGameMode)
{
	CurrentInGameMode = NewInGameMode;
	const UEnum* EnumPtr = StaticEnum<EInGameModes>();
	if (EnumPtr)
	{
		const FText NewText = FText::FromString(EnumPtr->GetNameStringByValue(static_cast<uint8>(NewInGameMode)));
		InGameMode->SetText(NewText);
	}
}

void UCharacterSelectWidget::RequestServerSetCPUCount(const int32& NewCount) const
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ServerRPCSetCPUCount(NewCount);	
	}
}

void UCharacterSelectWidget::RequestServerSetRuleCount(const int32& NewCount) const
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ServerRPCSetRuleCount(NewCount);
	}
}

void UCharacterSelectWidget::RequestServerChangeRule(const EInGameModes& NewInGameMode)
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ServerRPCChangeRule(NewInGameMode);	
	}
}


void UCharacterSelectWidget::OnBackButtonClicked()
{
	if (GetWorld())
	{
		auto* CurrentGameState = GetWorld()->GetGameState<AUMUMenuGameState>();
		if (CurrentGameState)
		{
			bool IsOnlineMode = CurrentGameState->GetIsOnlineMode();
			if (IsOnlineMode)
			{
				const int32 NewCount = CurrentGameState->GetNumberOfPlayers() - 1;
				CurrentGameState->SetNumberOfPlayers(NewCount);
				const FName MenuMapName = TEXT("menus");
				UGameplayStatics::OpenLevel(GetWorld(), MenuMapName);
			}
			else
			{
				RequestUpdateUIWidget(EMenuWidgetState::MainMenu);	
			}
		}
	}
}

void UCharacterSelectWidget::OnAddRuleCountClicked()
{
	const FString RuleCountToString = RuleCount->GetText().ToString();
	const int32 RuleCountToInt = FCString::Atoi(*RuleCountToString);
	if (RuleCountToInt >= 5)
	{
		return;
	}

	RequestServerSetRuleCount(RuleCountToInt + 1);
}

void UCharacterSelectWidget::OnSubtractRuleCountClicked()
{
	const FString RuleCountToString = RuleCount->GetText().ToString();
	const int32 RuleCountToInt = FCString::Atoi(*RuleCountToString);
	if (RuleCountToInt <= 1)
	{
		return;
	}

	RequestServerSetRuleCount(RuleCountToInt - 1);
}

void UCharacterSelectWidget::OnSubtractCPUCountClicked()
{
	const FString CPUCountToString = CPUCount->GetText().ToString();
	const int32 CPUCountToInt = FCString::Atoi(*CPUCountToString);
	if (CPUCountToInt <= 0)
	{
		return;
	}

	RequestServerSetCPUCount(CPUCountToInt - 1);
	CPUReady();
	RemovePlayerController();
}

void UCharacterSelectWidget::OnAddCPUCountClicked()
{
	const FString CPUCountToString = CPUCount->GetText().ToString();
	const int32 CPUCountToInt = FCString::Atoi(*CPUCountToString);
	if (CPUCountToInt >= CPUMaxCount)
	{
		return;
	}

	RequestServerSetCPUCount(CPUCountToInt + 1);
	CPUReady();
	CreatePlayerController();
}

void UCharacterSelectWidget::OnChangeRuleClicked()
{
	
	RequestServerChangeRule(CurrentInGameMode);
}

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(BackButton)
	check(RuleCount)
	check(CPUCount)
	check(AddCPUCountButton)
	check(SubtractCPUCountButton)
	check(AddRuleCountButton)
	check(SubtractRuleCountButton)
	check(InGameMode)
	
	BindClickEvent();
}

void UCharacterSelectWidget::BindClickEvent()
{
	check(BackButton)
	check(AddCPUCountButton)
	check(SubtractCPUCountButton)
	check(AddRuleCountButton)
	check(SubtractRuleCountButton)
	check(ChangeRuleButton)

	BackButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnBackButtonClicked);
	
	AddCPUCountButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnAddCPUCountClicked);
	SubtractCPUCountButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnSubtractCPUCountClicked);

	ChangeRuleButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnChangeRuleClicked);
	
	AddRuleCountButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnAddRuleCountClicked);
	SubtractRuleCountButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnSubtractRuleCountClicked);
}