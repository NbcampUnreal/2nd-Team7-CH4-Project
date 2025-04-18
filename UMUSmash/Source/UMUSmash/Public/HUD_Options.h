#pragma once

#include "EngineUtils.h"
#include "CoreMinimal.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "Blueprint/UserWidget.h"
#include "HUD_Options.generated.h"

class USlider;
class UComboBoxString;
class UButton;

UCLASS()
class UMUSMASH_API UHUD_Options : public UUserWidget
{
	GENERATED_BODY()
protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnBrightnessChanged(float Value);

    UFUNCTION()
    void OnSoundChanged(float Value);

    UFUNCTION()
    void OnGraphicsChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnApplyClicked();

public:
    // À§Á¬ ¹ÙÀÎµù
    UPROPERTY(meta = (BindWidget))
    USlider* BrightnessSlider;

    UPROPERTY(meta = (BindWidget))
    USlider* SoundSlider;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* GraphicsComboBox;

    UPROPERTY(meta = (BindWidget))
    UButton* ApplyButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundMix* GameSoundMix;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundClass* MasterSoundClass;

    UPROPERTY(meta = (BindWidget))
    UButton* BackButton;

    UFUNCTION(BlueprintCallable)
    void OnBackClicked();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HUD_MainMenuClass;

    UFUNCTION()
    void UpdateOptionUI();



private:
    float BrightnessValue = 1.0f;
    float SoundValue = 1.0f;
    FString GraphicsSetting = "High";
};