


#include "Widget/CharacterSelectWidget.h"

#include "Components/Button.h"
#include "Player/UMUMenuController.h"

void UCharacterSelectWidget::RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ChangeNextProgressUI(WidgetState);
	}
}

void UCharacterSelectWidget::OnBackButtonClicked()
{
	RequestUpdateUIWidget(EMenuWidgetState::MainMenu);
}

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(BackButton)

	BindClickEvent();
}

void UCharacterSelectWidget::BindClickEvent()
{
	check(BackButton)

	BackButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnBackButtonClicked);
}