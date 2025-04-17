

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectTileWidget.generated.h"


class UButton;

UCLASS()
class UMUSMASH_API UCharacterSelectTileWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void RequestServerSelectedCharacter(const ECharacter& SelectedCharacter);
	
	UFUNCTION()
	void OnCharacterSelectButtonClicked();
	
	virtual void NativeConstruct() override;

	void BindClickEvent();


	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CharacterSelectButton;

	UPROPERTY(BlueprintReadWrite)
	ECharacter Character;
};
