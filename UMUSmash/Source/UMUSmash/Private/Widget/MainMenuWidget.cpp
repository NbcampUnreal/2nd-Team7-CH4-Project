


#include "Widget/MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/UMUMenuController.h"

void UMainMenuWidget::BindClickEvent()
{
	check(SinglePlayButton)
	check(MultiPlayButton)
	check(SettingsButton)
	check(EndButton)

	SinglePlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSinglePlayButtonClicked);
	MultiPlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnMultiPlayButtonClicked);
	SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsButtonClicked);
	EndButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnEndButtonClicked);
}

void UMainMenuWidget::RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ChangeNextProgressUI(WidgetState);
	}
}

void UMainMenuWidget::OnSinglePlayButtonClicked()
{
	RequestUpdateUIWidget(EMenuWidgetState::CharacterSelect);
}

void UMainMenuWidget::OnMultiPlayButtonClicked()
{
	RequestUpdateUIWidget(EMenuWidgetState::NetworkLobby);
}

void UMainMenuWidget::OnSettingsButtonClicked()
{
	RequestUpdateUIWidget(EMenuWidgetState::Settings);
}

void UMainMenuWidget::OnEndButtonClicked()
{
	if (GetOwningPlayer())
	{
		if (GetOwningPlayer()->GetWorld())
		{
			UKismetSystemLibrary::QuitGame
			(
				GetOwningPlayer()->GetWorld(),
				GetOwningPlayer(),
				EQuitPreference::Quit,
				false
			);	
		}
	}
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(SinglePlayButton)
	check(MultiPlayButton)
	check(SettingsButton)
	check(EndButton)

	BindClickEvent();
}
