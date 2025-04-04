

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UMUTypes.h"
#include "UMUFightGameMode.generated.h"

class UUMUGameInstance;

UCLASS()
class UMUSMASH_API AUMUFightGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	// --- Main game flow
	void HandleInitGame();
	void SetPlayerStocks();
	void HandleGameOver() const;

	// --- Helper functions
	void CreatePlayers();
	bool OnlineLoaded();
	void MatchStats();
	
	void FinalizeGameStats() const;
	void TravelToVictoryScreen() const;
	

	// Getter & Setter Macro
	#define MAKE_GETTERSETTER(Type, Name) \
	UFUNCTION(BlueprintGetter) Type Get##Name() const { return Name; } \
	UFUNCTION(BlueprintSetter) void Set##Name(Type NewValue) { Name = NewValue; }

	#define MAKE_GETTERSETTER_REF(Type, Name) \
	UFUNCTION(BlueprintGetter) const Type& Get##Name() const { return Name; } \
	UFUNCTION(BlueprintSetter) void Set##Name(const Type& NewValue) { Name = NewValue; }

	#define MAKE_BOOL_GETTERSETTER(FunctionName, Name) \
	UFUNCTION(BlueprintGetter) bool FunctionName() const { return Name; } \
	UFUNCTION(BlueprintSetter) void Set##FunctionName(bool NewValue) { Name = NewValue; }

	
	MAKE_GETTERSETTER_REF(TObjectPtr<UUMUGameInstance>, Instance);

	MAKE_GETTERSETTER(int32, NumberOfPlayers);
	MAKE_GETTERSETTER_REF(TArray<int32>, Stocks);
	MAKE_GETTERSETTER(int32, NumPlayersAlive);

	MAKE_GETTERSETTER_REF(TArray<int32>, Elims);
	MAKE_GETTERSETTER_REF(TArray<int32>, Falls);
	MAKE_GETTERSETTER_REF(TArray<int32>, DamageDone);
	MAKE_GETTERSETTER_REF(TArray<int32>, DamageTaken);
	
	MAKE_GETTERSETTER_REF(EInGameModes, InGameMode);
	MAKE_GETTERSETTER(int32, Minutes);
	MAKE_BOOL_GETTERSETTER(UseTimer, bUseTimer);
	
	MAKE_BOOL_GETTERSETTER(ISGameOver, bIsGameOver);
	
	MAKE_GETTERSETTER_REF(TArray<bool>, PlayerLoaded);


protected:

	// --- Instance --- 
	TObjectPtr<UUMUGameInstance> Instance;

	// --- Stats ---
	int32 NumberOfPlayers;
	TArray<int32> Stocks;
	int32 NumPlayersAlive;

	TArray<int32> Elims;
	TArray<int32> Falls;
	TArray<int32> DamageDone;
	TArray<int32> DamageTaken;

	// --- Game Mode --- 
	EInGameModes InGameMode;
	
	int32 Minutes;
	bool bUseTimer;

	// --- Game flow ---
	TArray<bool> PlayerLoaded;
	bool bIsGameOver;

	virtual void BeginPlay() override;
};
