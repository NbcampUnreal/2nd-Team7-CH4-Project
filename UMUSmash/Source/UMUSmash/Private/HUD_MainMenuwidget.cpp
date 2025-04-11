#include "HUD_MainMenuWidget.h"
#include "Managers/UMUGameInstance.h"
#include "Managers/UMUFightGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UMU_Lobbycontroller.h"

void UHUD_MainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // --- Player Controller 캐스팅
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    LobbyControllerRef = Cast<AUMU_Lobbycontroller>(PC);

    // --- Game Instance 캐스팅
    GameInstanceRef = Cast<UUMUGameInstance>(GetGameInstance());

    // --- 서버일 때만 Gamemode 캐스팅
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
        // 커스텀 컨트롤러 함수나 상태 설정
    }
}
