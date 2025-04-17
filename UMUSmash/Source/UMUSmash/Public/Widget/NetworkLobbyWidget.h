#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "NetworkLobbyWidget.generated.h"

class UButton;

UCLASS()
class UMUSMASH_API UNetworkLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const;

protected:
	UFUNCTION()
	void OnBackButtonClicked();
	
	// EventBinding
	void BindClickEvent();
	
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;
};
