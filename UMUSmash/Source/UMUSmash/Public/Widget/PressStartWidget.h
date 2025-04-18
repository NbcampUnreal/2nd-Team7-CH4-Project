

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PressStartWidget.generated.h"

class UButton;

UCLASS()
class UMUSMASH_API UPressStartWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	void RequestMainMenuWidget() const;
	
	// EventBinding
	void BindClickEvent();
	UFUNCTION()
	void OnButtonClicked();

	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Button;
};
