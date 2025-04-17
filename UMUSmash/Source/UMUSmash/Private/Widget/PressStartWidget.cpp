


#include "Widget/PressStartWidget.h"

#include "Components/Button.h"
#include "Player/UMUMenuController.h"
#include "UMUTypes.h"

void UPressStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 위젯 바인딩 확인
	check(Button);

	// 이벤트 바인딩
	BindClickEvent();
}

void UPressStartWidget::BindClickEvent()
{
	ensure(Button);

	Button->OnClicked.AddDynamic(this, &UPressStartWidget::OnButtonClicked);
}

void UPressStartWidget::OnButtonClicked()
{
	RequestMainMenuWidget();	
}

void UPressStartWidget::RequestMainMenuWidget() const
{
	auto* MenuController = Cast<AUMUMenuController>(GetOwningPlayer());
	if (MenuController)
	{
		MenuController->ChangeNextProgressUI(EMenuWidgetState::MainMenu);
	}
}
