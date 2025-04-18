

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

UCLASS()
class UMUSMASH_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const;

	
protected:
	UFUNCTION()
	void OnSinglePlayButtonClicked();
	UFUNCTION()
	void OnMultiPlayButtonClicked();
	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION()
	void OnEndButtonClicked();
	
	// EventBinding
	void BindClickEvent();
	
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SinglePlayButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* MultiPlayButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SettingsButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* EndButton;
	
};


