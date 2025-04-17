

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "HUDLobby.generated.h"

class UCharacterSelectWidget;
class UMapSelectWidget;

UCLASS()
class UMUSMASH_API UHUDLobby : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateUIToProgress(const EMenuWidgetState& NextWidgetState) const;
	void InitWidget() const;
	TObjectPtr<UCharacterSelectWidget> GetCharacterSelectWidget() const { return LobbyCharacterSelect; }

protected:
	virtual void NativeConstruct() override;
	
	void AllWidgetDisable() const;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCharacterSelectWidget> LobbyCharacterSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMapSelectWidget> LobbyMapSelect;
};
