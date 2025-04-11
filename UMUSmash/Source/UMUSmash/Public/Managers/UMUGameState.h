

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
	AUMUGameState();

	/// --- RPC ---
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCIsGameOver();

	// --- Rule ---
	void SlowMotionEffect();
	void UpdateIsGameOver();
	void UpdatePlayerLoaded();
	
	void StartCountdown();
	UFUNCTION()
	void UpdateCountdown();
	UFUNCTION()
	void OnRep_UpdateSeconds();
	void UpdateInterpolatedTime();
	

	void InitState();


	// --- getter & setter ---
	double GetInterpolatedTime() const { return InterpolatedTime; }
	EInGameModes GetInGameMode() const { return InGameMode; }
	
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// --- Life cycle ---
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	FTimerHandle FinalGameStatsHandle;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Mode", meta=(AllowPrivateAccess="true"))
	EInGameModes InGameMode;

	UPROPERTY(BlueprintReadWrite, Category="Game.DefaultClass", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UUMUGameInstance> GameInstance;
	UPROPERTY(BlueprintReadWrite, Category="Game.DefaultClass", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AUMUFightGameMode> GameMode;

	UPROPERTY(Replicated, BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	bool bUseTimer;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	int32 Minutes;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	double DeltaSeconds;
	UPROPERTY(ReplicatedUsing = OnRep_UpdateSeconds, BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	double Seconds;
	UPROPERTY(BlueprintReadWrite, Category="Game.Timer", meta=(AllowPrivateAccess="true"))
	FString TimerText;

	
	FTimerHandle CountdownTimerHandle;
	float CountdownEndTime;
	float LastReplicatedSeconds;
	float LastReplicatedTimestamp;
	float InterpolatedTime;

	
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

inline void AUMUGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(FinalGameStatsHandle);
}
