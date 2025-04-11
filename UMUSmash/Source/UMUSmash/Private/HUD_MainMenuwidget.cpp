#include "HUD_MainMenuWidget.h"
#include "Managers/UMUGameInstance.h"
#include "Managers/UMUFightGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UMU_Lobbycontroller.h"

void UHUD_MainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // --- Player Controller ĳ����
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    LobbyControllerRef = Cast<AUMU_Lobbycontroller>(PC);

    // --- Game Instance ĳ����
    GameInstanceRef = Cast<UUMUGameInstance>(GetGameInstance());

    // --- ������ ���� Gamemode ĳ����
    if (GetWorld()->GetNetMode() != NM_Client)
    {
        GameModeRef = Cast<AUMUFightGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    }

}


void UHUD_MainMenuWidget::InitReferences()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    LobbyControllerRef = Cast<AUMU_Lobbycontroller>(PC);

    GameInstanceRef = Cast<UUMUGameInstance>(GetGameInstance());

    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        GameModeRef = Cast<AUMUFightGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    }
}


void UHUD_MainMenuWidget::SelectOnlineMode()
{
    if (LobbyControllerRef)
    {
        // Ŀ���� ��Ʈ�ѷ� �Լ��� ���� ����
    }
}
