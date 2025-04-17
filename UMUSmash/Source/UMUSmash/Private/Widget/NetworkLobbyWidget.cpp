


#include "Widget/NetworkLobbyWidget.h"

#include "Components/Button.h"
#include "Player/UMUMenuController.h"

void UNetworkLobbyWidget::RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ChangeNextProgressUI(WidgetState);
	}
}

void UNetworkLobbyWidget::OnBackButtonClicked()
{
	RequestUpdateUIWidget(EMenuWidgetState::MainMenu);
}

void UNetworkLobbyWidget::BindClickEvent()
{
	check(BackButton);
	
	BackButton->OnClicked.AddDynamic(this, &UNetworkLobbyWidget::OnBackButtonClicked);
}

void UNetworkLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(BackButton);

	BindClickEvent();
}
