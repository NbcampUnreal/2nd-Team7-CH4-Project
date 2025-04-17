

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "SelectedCharacterPanelWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class UMUSMASH_API USelectedCharacterPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:


protected:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY(BlueprintReadWrite)
	ECharacter PanelSelectedCharacter;
	
	UPROPERTY(BlueprintReadOnly)
	FText PanelPlayerName;
	
	UPROPERTY(BlueprintReadOnly)
	FText PanelCharacterName;
};
