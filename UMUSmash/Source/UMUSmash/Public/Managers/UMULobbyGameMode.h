

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UMULobbyGameMode.generated.h"

UCLASS()
class UMUSMASH_API AUMULobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:


protected:
	void SetIsOnlineMode() const;

	virtual void BeginPlay() override;
};
