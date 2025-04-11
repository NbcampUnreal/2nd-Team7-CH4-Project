#include "UMU_Lobbycontroller.h"
#include "Kismet/GameplayStatics.h"


UMUGameInstance* AUMU_Lobbycontroller::GetMyGameInstance()
{
    return Cast<UMUGameInstance>(GetGameInstance());
}

UMUFightGameMode* AUMU_Lobbycontroller::GetMyGameMode()
{
    return Cast<UMUFightGameMode>(UGameplayStatics::GetGameMode(this));
}