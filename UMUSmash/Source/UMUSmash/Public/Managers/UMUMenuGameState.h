

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "GameFramework/GameStateBase.h"
#include "UMUMenuGameState.generated.h"



UCLASS()
class UMUSMASH_API AUMUMenuGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Game Rule
	void CheckAllPlayerReady();
	void CheckCPUArray();
	// void RandomMapTravel() const;
	
	// Getter & Setter
	void SetIsOnlineMode(const bool& NewValue) { bIsOnlineMode = NewValue; };
	bool GetIsOnlineMode() const { return bIsOnlineMode; };
	void SetNumberOfPlayers(const int& NewValue);
	int32 GetNumberOfPlayers() const { return NumberOfPlayers; };
	void SetCPUCount(const int32& NewValue);
	void SetRuleCount(const int32& NewValue);
	void SetPlayerCharactersArray(const int32& PlayerID, const ECharacter& SelectedCharacter);
	void SetPlayerReadyArray(const int32& PlayerID, const bool& bIsReady);

	void ChangeRule(const EInGameModes& NewInGameMode);

	
protected:
	UFUNCTION()
	void OnRep_IsOnlineMode();
	UFUNCTION()
	void OnRep_NumberOfPlayers();
	UFUNCTION()
	void OnRep_CPUCount() const;
	UFUNCTION()
	void OnRep_InGameMode();
	UFUNCTION()
	void OnRep_StockCount();
	UFUNCTION()
	void OnRep_Minutes();

	UFUNCTION(BlueprintCallable)
	FString RandomMapSelect() const;
	UFUNCTION(BlueprintCallable)
	void SaveGameData() const;
	void FitToSizeArray();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	TArray<bool> ReadyArray = {};
	int32 PlayerNumber = 0;

	UPROPERTY(ReplicatedUsing = OnRep_CPUCount)
	int32 CPUCount = 0;
	
	UPROPERTY(ReplicatedUsing = OnRep_IsOnlineMode, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsOnlineMode = false;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bAllPlayersReady = false;
	
	// Send To GameInstance
	UPROPERTY(ReplicatedUsing = OnRep_NumberOfPlayers)
	int32 NumberOfPlayers = 0;
	
	TArray<ECharacter> PlayerCharacters = {};
	
	TArray<bool> CPUCheckArray = {};
	
	UPROPERTY(ReplicatedUsing = OnRep_InGameMode)
	EInGameModes InGameMode = EInGameModes::Stock;

	UPROPERTY(ReplicatedUsing = OnRep_StockCount)
	int32 StockCount = 3;

	UPROPERTY(ReplicatedUsing = OnRep_Minutes)
	int32 Minutes = 3;
};
