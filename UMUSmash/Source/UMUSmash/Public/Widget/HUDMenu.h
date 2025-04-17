

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "HUDMenu.generated.h"

class UPressStartWidget;
class UMainMenuWidget;
class UCharacterSelectWidget;
class UMapSelectWidget;
class USettingsWidget;
class UNetworkLobbyWidget;

UCLASS()
class UMUSMASH_API UHUDMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateUIToProgress(const EMenuWidgetState& NextWidgetState) const;
	void InitWidget() const;
	
	// Getter & Setter
	TObjectPtr<UPressStartWidget> GetPressStartWidget() const {return PressStart;}
	TObjectPtr<UMainMenuWidget> GetMainMenuWidget() const {return MainMenu;}
	TObjectPtr<UCharacterSelectWidget> GetCharacterSelectWidget() const {return CharacterSelect;}
	
	
protected:
	virtual void NativeConstruct() override;
	
	void AllWidgetDisable() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPressStartWidget> PressStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMainMenuWidget> MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCharacterSelectWidget> CharacterSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMapSelectWidget> MapSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNetworkLobbyWidget> NetworkLobby;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USettingsWidget> SettingsWidget;
};
