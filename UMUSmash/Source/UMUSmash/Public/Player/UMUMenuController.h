

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "GameFramework/PlayerController.h"
#include "UMUMenuController.generated.h"

class UHUDMenu;

UCLASS()
class UMUSMASH_API AUMUMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	void BlockClientInput();
	void SetUseCursor(const bool& bUseCursor);

	void ChangeNextProgressUI(EMenuWidgetState NextWidgetState);
	
	// Getter & Setter
	TObjectPtr<UHUDMenu> GetHUDMenuInstance() const { return HUDMenuInstance; }
	

protected:
	virtual void BeginPlay() override;

	void AddHUDWidget();


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UHUDMenu> HUDMenuClass;
	TObjectPtr<UHUDMenu> HUDMenuInstance;
	
};
