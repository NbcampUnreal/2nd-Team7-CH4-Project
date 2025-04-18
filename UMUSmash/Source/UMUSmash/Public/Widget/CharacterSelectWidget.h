

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

class UCharacterSelectTileWidget;
class USelectedCharacterPanelWidget;
class UButton;
class UTextBlock;

UCLASS()
class UMUSMASH_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void RequestUpdateUIWidget(const EMenuWidgetState WidgetState) const;
	void UpdateRuleCount(const int32& NewCount);
	void UpdateCPUCount(const int32& NewCount) const;
	void UpdateCPUMaxCount(const int32& NewCount);
	void UpdateInGameMode(const EInGameModes& NewInGameMode);
	void RequestServerSetCPUCount(const int32& NewCount) const;
	void RequestServerSetRuleCount(const int32& NewCount) const;
	void RequestServerChangeRule(const EInGameModes& NewInGameMode);
	
	UFUNCTION(BlueprintImplementableEvent)
	void CPUReady();

protected:
	UFUNCTION()
	void OnBackButtonClicked();
	UFUNCTION()
	void OnAddRuleCountClicked();
	UFUNCTION()
	void OnSubtractRuleCountClicked();
	UFUNCTION()
	void OnSubtractCPUCountClicked();
	UFUNCTION()
	void OnAddCPUCountClicked();
	UFUNCTION()
	void OnChangeRuleClicked();
	
	virtual void NativeConstruct() override;

	void BindClickEvent();


protected:
	EInGameModes CurrentInGameMode;
	int32 StockCount;
	int32 Minutes;
	int32 CPUMaxCount = 3;

	// Widget
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* RuleCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CPUCount;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* InGameMode;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ChangeRuleButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* AddCPUCountButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SubtractCPUCountButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* AddRuleCountButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SubtractRuleCountButton;
	
};
