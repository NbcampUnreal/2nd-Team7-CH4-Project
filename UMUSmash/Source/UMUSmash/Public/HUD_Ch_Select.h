#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_Ch_Select.generated.h"


UENUM(BlueprintType)
enum class EGameModeType : uint8
{
    Stock UMETA(DisplayName = "Stock"),
    Time  UMETA(DisplayName = "Time")
};

USTRUCT(BlueprintType)
struct FPlayerSlotData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCPU = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCharacterSelected = false;
};


UCLASS()
class UMUSMASH_API UHUD_Ch_Select : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
    void TryPlayPressStart();

    UFUNCTION(BlueprintCallable)
    void OpenMapScreenIfReady();

    UFUNCTION(BlueprintCallable)
    void OnQ1ToggleClicked();

    UFUNCTION(BlueprintCallable)
    void OnGoBackClicked();

    UFUNCTION(BlueprintCallable)
    void ToggleGameMode();

    UFUNCTION(BlueprintCallable)
    void ToggleCPUSlot(int32 SlotIndex);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby")
    TArray<FPlayerSlotData> PlayerSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby")
    EGameModeType GameMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby")
    bool bQ1Enabled = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby")
    bool bCharactersReady = false;

    UPROPERTY(meta = (BindWidget))
    class UWidget* MapScreenWidget;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    class UWidgetAnimation* PressStartAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HUD_MainMenuClass;

private:
    bool AreAllCharactersSelected() const;

    void UpdateQ1UI();
    void UpdateGameModeUI();
    void UpdateCPUSlotUI(int32 SlotIndex);

};
