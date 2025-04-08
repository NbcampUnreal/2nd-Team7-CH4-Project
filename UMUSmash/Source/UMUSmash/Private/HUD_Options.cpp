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
    }

    if (ApplyButton)
    {
        ApplyButton->OnClicked.AddDynamic(this, &UHUD_Options::OnApplyClicked);
    }

    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UHUD_Options::OnBackClicked);
    }

    UpdateOptionUI();
}


void UHUD_Options::OnBrightnessChanged(float Value)
{
    BrightnessValue = Value;
}

void UHUD_Options::OnSoundChanged(float Value)
{
    SoundValue = Value;

    if (GameSoundMix && MasterSoundClass)
    {
        UGameplayStatics::SetSoundMixClassOverride(
            GetWorld(),
            GameSoundMix,
            MasterSoundClass,
            Value,   // Volume (0.0 ~ 1.0)
            1.0f,    // Pitch
            0.0f     // FadeInTime
        );

        UGameplayStatics::PushSoundMixModifier(GetWorld(), GameSoundMix);
    }
}


void UHUD_Options::OnGraphicsChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    GraphicsSetting = SelectedItem;
    UE_LOG(LogTemp, Warning, TEXT("Graphics Selected: %s"), *GraphicsSetting);
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
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        FString Command;

        if (GraphicsSetting == "Low")
        {
            Command = "sg.ViewDistanceQuality 1; sg.AntiAliasingQuality 1; sg.ShadowQuality 1; sg.TextureQuality 1;";
        }
        else if (GraphicsSetting == "Medium")
        {
            Command = "sg.ViewDistanceQuality 2; sg.AntiAliasingQuality 2; sg.ShadowQuality 2; sg.TextureQuality 2;";
        }
        else if (GraphicsSetting == "High")
        {
            Command = "sg.ViewDistanceQuality 3; sg.AntiAliasingQuality 3; sg.ShadowQuality 3; sg.TextureQuality 3;";
        }

        if (!Command.IsEmpty())
        {
            PC->ConsoleCommand(Command, true);
        }
    }
}

void UHUD_Options::OnBackClicked()
{
    // 현재 위젯 제거
    RemoveFromParent();

    // MainMenu 위젯 클래스를 불러와 생성
    if (UWorld* World = GetWorld())
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
        if (PC && HUD_MainMenuClass)
        {
            UUserWidget* MainMenu = CreateWidget<UUserWidget>(PC, HUD_MainMenuClass);
            if (MainMenu)
            {
                MainMenu->AddToViewport();
                PC->SetInputMode(FInputModeUIOnly());
                PC->bShowMouseCursor = true;
            }
        }
    }
}

void UHUD_Options::UpdateOptionUI()
{

    for (TActorIterator<APostProcessVolume> It(GetWorld()); It; ++It)
    {
        APostProcessVolume* PPV = *It;
        if (PPV && PPV->bUnbound)
        {
            BrightnessValue = PPV->Settings.AutoExposureMinBrightness;
            if (BrightnessSlider)
            {
                BrightnessSlider->SetValue(BrightnessValue);
            }
            break;
        }
    }


    if (SoundSlider)
    {
        SoundSlider->SetValue(SoundValue);
    }


    if (GraphicsComboBox)
    {
        GraphicsComboBox->SetSelectedOption(GraphicsSetting);
    }
}
