#include "HUD_Ch_Select.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"

void UHUD_Ch_Select::TryPlayPressStart()
{
    if (AreAllCharactersSelected())
    {
        if (PressStartAnim)
        {
            PlayAnimation(PressStartAnim);
        }
    }
}

bool UHUD_Ch_Select::AreAllCharactersSelected() const
{
    int32 SelectedCount = 0;
    for (const FPlayerSlotData& PlayerSlot : PlayerSlots)
    {
        if (PlayerSlot.bIsCharacterSelected)
        {
            ++SelectedCount;
        }
    }
    return SelectedCount == PlayerSlots.Num();
}


void UHUD_Ch_Select::OpenMapScreenIfReady()
{
    if (bCharactersReady && MapScreenWidget)
    {
        MapScreenWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void UHUD_Ch_Select::OnQ1ToggleClicked()
{
    bQ1Enabled = !bQ1Enabled;
    UpdateQ1UI();
}

void UHUD_Ch_Select::OnGoBackClicked()
{
    RemoveFromParent();

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


void UHUD_Ch_Select::ToggleGameMode()
{
    GameMode = (GameMode == EGameModeType::Stock) ? EGameModeType::Time : EGameModeType::Stock;
    UpdateGameModeUI();
}

void UHUD_Ch_Select::ToggleCPUSlot(int32 SlotIndex)
{
    if (PlayerSlots.IsValidIndex(SlotIndex))
    {
        PlayerSlots[SlotIndex].bIsCPU = !PlayerSlots[SlotIndex].bIsCPU;
        UpdateCPUSlotUI(SlotIndex);
    }
}

void UHUD_Ch_Select::UpdateQ1UI()
{

}

void UHUD_Ch_Select::UpdateGameModeUI()
{

}

void UHUD_Ch_Select::UpdateCPUSlotUI(int32 SlotIndex)
{

}
