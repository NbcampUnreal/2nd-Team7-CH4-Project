


#include "Widget/HUDMenu.h"

#include "Managers/UMUMenuGameMode.h"
#include "Widget/CharacterSelectWidget.h"
#include "Widget/MainMenuWidget.h"
#include "Widget/PressStartWidget.h"
#include "Widget/MapSelectWidget.h"
#include "Widget/NetworkLobbyWidget.h"
#include "Widget/SettingsWidget.h"

void UHUDMenu::NativeConstruct()
{
	Super::NativeConstruct();

	check(PressStart)
	check(MainMenu)
	check(CharacterSelect)
	check(MapSelect)
	check(NetworkLobby)
	check(SettingsWidget)

	InitWidget();
	
	if (GetWorld())
	{
		MenuGameModeInstance = Cast<AUMUMenuGameMode>(GetWorld()->GetAuthGameMode());
	}

	check(MenuGameModeInstance)
}

void UHUDMenu::InitWidget() const
{
	AllWidgetDisable();
	
	// 초기에 쓸 위젯
	PressStart->SetIsEnabled(true);
	PressStart->SetVisibility(ESlateVisibility::Visible);
}

void UHUDMenu::UpdateUIToProgress(const EMenuWidgetState& NextWidgetState) const
{
	AllWidgetDisable();
	switch (NextWidgetState)
	{
		case EMenuWidgetState::PressStart:
		{
			PressStart->SetIsEnabled(true);
			PressStart->SetVisibility(ESlateVisibility::Visible);
			break;
		}
		case EMenuWidgetState::MainMenu:
		{
			MainMenu->SetIsEnabled(true);
			MainMenu->SetVisibility(ESlateVisibility::Visible);
			break;
		}
		case EMenuWidgetState::CharacterSelect:
		{
			CharacterSelect->SetIsEnabled(true);
			CharacterSelect->SetVisibility(ESlateVisibility::Visible);
			break;		
		}
		case EMenuWidgetState::MapSelect:
		{
			MapSelect->SetIsEnabled(true);
			MapSelect->SetVisibility(ESlateVisibility::Visible);
			break;		
		}
		case EMenuWidgetState::NetworkLobby:
		{
			NetworkLobby->SetIsEnabled(true);
			NetworkLobby->SetVisibility(ESlateVisibility::Visible);
			break;
		}
		case EMenuWidgetState::Settings:
		{
			SettingsWidget->SetIsEnabled(true);
			SettingsWidget->SetVisibility(ESlateVisibility::Visible);
			break;
		}
		default:
		{
			PressStart->SetIsEnabled(true);
			PressStart->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}
	MenuGameModeInstance->SetWidgetState(NextWidgetState);
}


void UHUDMenu::AllWidgetDisable() const
{
	PressStart->SetIsEnabled(false);
	PressStart->SetVisibility(ESlateVisibility::Hidden);
	
	MainMenu->SetIsEnabled(false);
	MainMenu->SetVisibility(ESlateVisibility::Hidden);

	CharacterSelect->SetIsEnabled(false);
	CharacterSelect->SetVisibility(ESlateVisibility::Hidden);

	MapSelect->SetIsEnabled(false);
	MapSelect->SetVisibility(ESlateVisibility::Hidden);

	NetworkLobby->SetIsEnabled(false);
	NetworkLobby->SetVisibility(ESlateVisibility::Hidden);
	
	SettingsWidget->SetIsEnabled(false);
	SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
}
