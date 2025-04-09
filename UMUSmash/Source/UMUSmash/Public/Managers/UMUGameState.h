

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "GameFramework/GameStateBase.h"
#include "UMUGameState.generated.h"

class UUMUGameInstance;
class AUMUFightGameMode;

UCLASS()
class UMUSMASH_API AUMUGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	/// --- RPC ---
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCIsGameOver();

	// ---
	void SlowMotionEffect() const;
	void UpdateIsGameOver();
	void UpdatePlayerLoaded();


	void InitState();

	// --- Replication ---
	// UFUNCTION()
	// void OnRep_IsAllLoaded();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// --- Life cycle ---
	virtual void BeginPlay() override;


private:
	UPROPERTY(BlueprintReadWrite, Category="Game.Mode", meta=(AllowPrivateAccess="true"))
	EInGameModes InGameMode;

	UPROPERTY(BlueprintReadWrite, Category="Game.DefaultClass", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UUMUGameInstance> GameInstance;
	UPROPERTY(BlueprintReadWrite, Category="Game.DefaultClass", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AUMUFightGameMode> GameMode;

	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	bool bUseTimer;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	int32 Minutes;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	double DeltaSeconds;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	double Seconds;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	FString TimerText;

	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 NumPlayersAlive;
	UPROPERTY(Replicated, BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> PlayerLoaded;
	UPROPERTY(Replicated, BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	bool bIsAllLoaded;

	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Elims;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Falls;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageDone;
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageTaken;

	bool bIsGameOver;
};
