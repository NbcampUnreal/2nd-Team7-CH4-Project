

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "GameFramework/GameModeBase.h"
#include "UMUMenuGameMode.generated.h"


UCLASS()
class UMUSMASH_API AUMUMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	void ServerTravelToNextMap();
	void SetWidgetState(const EMenuWidgetState& NextWidgetState) { WidgetState = NextWidgetState; };



protected:
	AUMUMenuGameMode();
	

	virtual void PostLogin(APlayerController* NewPlayer) override;


protected:
	EMaps NextMap;
	EMenuWidgetState WidgetState;

	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 NumberOfPlayer = 0;

	bool bBlockAddClient = false;
};
