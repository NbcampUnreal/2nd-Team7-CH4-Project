#pragma once

#include "Managers/UMUGameInstance.h"
#include "Managers/UMUFightGameMode.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UMU_Lobbycontroller.generated.h"


UCLASS()
class UMUSMASH_API AUMU_Lobbycontroller : public APlayerController
{
	GENERATED_BODY()
	
public:
	class UMUGameInstance* GetMyGameInstance();
	class UMUFightGameMode* GetMyGameMode();
};
