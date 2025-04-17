


#include "Widget/CharacterSelectTileWidget.h"

#include "Components/Button.h"
#include "Player/UMUMenuController.h"

void UCharacterSelectTileWidget::RequestServerSelectedCharacter(const ECharacter& SelectedCharacter)
{
	
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ServerRPCSelectedCharacter(SelectedCharacter);	
	}
}

void UCharacterSelectTileWidget::OnCharacterSelectButtonClicked()
{
	RequestServerSelectedCharacter(Character);
}

void UCharacterSelectTileWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(CharacterSelectButton);

	BindClickEvent();
}

void UCharacterSelectTileWidget::BindClickEvent()
{
	check(CharacterSelectButton);

	CharacterSelectButton->OnClicked.AddDynamic(this, &UCharacterSelectTileWidget::OnCharacterSelectButtonClicked);
}
