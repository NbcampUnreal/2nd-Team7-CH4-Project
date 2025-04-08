

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "GameFramework/GameModeBase.h"
#include "UMUFightGameMode.generated.h"

class UUMUGameInstance;

UCLASS()
class UMUSMASH_API AUMUFightGameMode : public AGameModeBase
{
	GENERATED_BODY()



private:
	UPROPERTY(BlueprintReadWrite, Category="Game.Mode", meta=(AllowPrivateAccess="true"))
	EInGameModes InGameMode;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.DefaultClass", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UUMUGameInstance> GameInstance;

	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	bool bUseTimer;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	int32 Minutes;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	double Seconds;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	FString TimerText;

	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 NumberOfPlayers;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 NumPlayersAlive;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Elims;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> SelfElim;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Falls;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageDone;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageTaken;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> PlayerLoaded;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	bool bAllLoaded;

	
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bIsDebugMode;
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bHideHitBoxes;

	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	bool bIsGameOver;

	
};
