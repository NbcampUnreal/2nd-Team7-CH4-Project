

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

class UButton;

UCLASS()
class UMUSMASH_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const;
	

protected:
	UFUNCTION()
	void OnBackButtonClicked();
	
	virtual void NativeConstruct() override;

	void BindClickEvent();


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;
};
