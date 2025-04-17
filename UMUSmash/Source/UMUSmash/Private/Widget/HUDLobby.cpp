


#include "Widget/HUDLobby.h"

#include "Widget/CharacterSelectWidget.h"
#include "Widget/MapSelectWidget.h"

void UHUDLobby::UpdateUIToProgress(const EMenuWidgetState& NextWidgetState) const
{
	AllWidgetDisable();
	
	if (NextWidgetState == EMenuWidgetState::CharacterSelect)
	{
		LobbyCharacterSelect->SetIsEnabled(true);
		LobbyCharacterSelect->SetVisibility(ESlateVisibility::Visible);
	}
	if (NextWidgetState == EMenuWidgetState::MapSelect)
	{
		LobbyMapSelect->SetIsEnabled(true);
		LobbyMapSelect->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHUDLobby::InitWidget() const
{
	AllWidgetDisable();

	// 초기에 쓸 위젯
	LobbyCharacterSelect->SetIsEnabled(true);
	LobbyCharacterSelect->SetVisibility(ESlateVisibility::Visible);
	
}

void UHUDLobby::NativeConstruct()
{
	Super::NativeConstruct();

	check(LobbyCharacterSelect)
	check(LobbyMapSelect)
}

void UHUDLobby::AllWidgetDisable() const
{
	LobbyCharacterSelect->SetIsEnabled(false);
	LobbyCharacterSelect->SetVisibility(ESlateVisibility::Hidden);

	LobbyMapSelect->SetIsEnabled(false);
	LobbyMapSelect->SetVisibility(ESlateVisibility::Hidden);
}
