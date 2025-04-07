#include "HUD_Options.h"
#include "EngineUtils.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "Engine/PostProcessVolume.h"

void UHUD_Options::NativeConstruct()
{
    Super::NativeConstruct();

    if (BrightnessSlider)
    {
        BrightnessSlider->OnValueChanged.AddDynamic(this, &UHUD_Options::OnBrightnessChanged);
    }

    if (SoundSlider)
    {
        SoundSlider->OnValueChanged.AddDynamic(this, &UHUD_Options::OnSoundChanged);
    }

    if (GraphicsComboBox)
    {
        GraphicsComboBox->OnSelectionChanged.AddDynamic(this, &UHUD_Options::OnGraphicsChanged);
        GraphicsComboBox->ClearOptions();
        GraphicsComboBox->AddOption("Low");
        GraphicsComboBox->AddOption("Medium");
        GraphicsComboBox->AddOption("High");
        GraphicsComboBox->SetSelectedOption("High");
    }

    if (ApplyButton)
    {
        ApplyButton->OnClicked.AddDynamic(this, &UHUD_Options::OnApplyClicked);
    }
}

void UHUD_Options::OnBrightnessChanged(float Value)
{
    BrightnessValue = Value;
}

void UHUD_Options::OnSoundChanged(float Value)
{
    SoundValue = Value;

    // 예: 마스터 볼륨 조절
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), nullptr, nullptr, Value, 1.0f, 0.0f);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), nullptr);
}

void UHUD_Options::OnGraphicsChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    GraphicsSetting = SelectedItem;
}

void UHUD_Options::OnApplyClicked()
{
    UWorld* World = GetWorld();
    if (!World) return;

    for (TActorIterator<APostProcessVolume> It(World); It; ++It)
    {
        APostProcessVolume* PPV = *It;
        if (PPV && PPV->bUnbound)
        {
            PPV->Settings.AutoExposureMinBrightness = BrightnessValue;
            PPV->Settings.AutoExposureMaxBrightness = BrightnessValue;
            break;
        }
    }

    // 그래픽 품질 설정
    FString Command;
    if (GraphicsSetting == "Low")
    {
        Command = "sg.ViewDistance 1; sg.AntiAliasing 1; sg.ShadowQuality 1; sg.TextureQuality 1;";
    }
    else if (GraphicsSetting == "Medium")
    {
        Command = "sg.ViewDistance 2; sg.AntiAliasing 2; sg.ShadowQuality 2; sg.TextureQuality 2;";
    }
    else if (GraphicsSetting == "High")
    {
        Command = "sg.ViewDistance 3; sg.AntiAliasing 3; sg.ShadowQuality 3; sg.TextureQuality 3;";
    }

    if (!Command.IsEmpty())
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
        if (PC)
        {
            PC->ConsoleCommand(Command, true);
        }
    }
}
