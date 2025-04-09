

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "UMUGameInstance.generated.h"

UCLASS()
class UMUSMASH_API UUMUGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()



public:
	UFUNCTION(BlueprintCallable, Category="Game")
	void ServerTravel(const FString& MapName) const;
	
	bool IsGameOver() const;
	void SetIsGameOver(const bool& NewValue);

	UFUNCTION(BlueprintCallable, Category="Game.Players")
	void CheckGameOverConditions();

	
#pragma region Getter & Setter Macro
	#define MAKE_GETTERSETTER(Type, Name) \
	UFUNCTION(BlueprintGetter) Type Get##Name() const { return Name; } \
	UFUNCTION(BlueprintSetter) void Set##Name(Type NewValue) { Name = NewValue; }

	#define MAKE_GETTERSETTER_REF(Type, Name) \
	UFUNCTION(BlueprintGetter) const Type& Get##Name() const { return Name; } \
	UFUNCTION(BlueprintSetter) void Set##Name(const Type& NewValue) { Name = NewValue; }

	#define MAKE_BOOL_GETTERSETTER(FunctionName, Name) \
	UFUNCTION(BlueprintGetter) bool FunctionName() const { return Name; } \
	UFUNCTION(BlueprintSetter) void Set##FunctionName(bool NewValue) { Name = NewValue; }


	// --- Color ---
	MAKE_GETTERSETTER(FSlateColor, P1_Col)
	MAKE_GETTERSETTER(FSlateColor, P2_Col)
	MAKE_GETTERSETTER(FSlateColor, P3_Col)
	MAKE_GETTERSETTER(FSlateColor, P4_Col)
	
	// --- Online ---
	MAKE_BOOL_GETTERSETTER(IsOnline, bIsOnline)
	MAKE_BOOL_GETTERSETTER(IsHost, bIsHost)
	MAKE_BOOL_GETTERSETTER(IsReady, bIsReady)
	MAKE_GETTERSETTER_REF(TArray<bool>, ReadyArray)

	// --- Players ---
	MAKE_GETTERSETTER(TSubclassOf<ACharacter>, Fighters)
	MAKE_GETTERSETTER_REF(TArray<ECharacter>, PlayerCharacters)
	MAKE_GETTERSETTER(int32, PlayerNumber)
	MAKE_GETTERSETTER(int32, NumberOfPlayers)
	MAKE_GETTERSETTER_REF(TArray<AController*>, PlayerControllers)
	MAKE_GETTERSETTER_REF(TArray<int32>, PlayerNumberIDs)
	MAKE_GETTERSETTER_REF(TArray<int32>, Elims)
	MAKE_GETTERSETTER_REF(TArray<int32>, SelfElim)
	MAKE_GETTERSETTER_REF(TArray<int32>, Falls)
	MAKE_GETTERSETTER_REF(TArray<int32>, DamageDone)
	MAKE_GETTERSETTER_REF(TArray<int32>, DamageTaken)
	MAKE_GETTERSETTER(TArray<int32>, PlayerPositions)
	MAKE_GETTERSETTER_REF(TArray<int32>, Score)
	MAKE_GETTERSETTER_REF(TArray<bool>, AliveArray)
	MAKE_GETTERSETTER_REF(TArray<bool>, CPU)
	MAKE_GETTERSETTER_REF(TArray<int32>, PlayerTeam)

	// --- Game Loop ---
	MAKE_GETTERSETTER(int32, StockCount)
	MAKE_GETTERSETTER(int32, Min)
	MAKE_BOOL_GETTERSETTER(IsLoopEnabled, bIsLoopEnabled)
	MAKE_GETTERSETTER(EGameModes, MainGameMode)
	MAKE_GETTERSETTER(EInGameModes, SubGameMode)
	MAKE_GETTERSETTER(int32, NumPlayersAlive)
	MAKE_GETTERSETTER(int32, WinnerPlayerID)

	// --- Menu ---
	MAKE_GETTERSETTER_REF(TArray<bool>, ActiveControllers)
	MAKE_GETTERSETTER(EMenus, Menus)

	// --- Debug ---
	MAKE_BOOL_GETTERSETTER(IsDebugMode, bIsDebugMode)
	MAKE_BOOL_GETTERSETTER(ShowDamageBoxes, bShowDamageBoxes)
	MAKE_BOOL_GETTERSETTER(ShowStates, bShowStates)

	// --- Team ---
	MAKE_BOOL_GETTERSETTER(IsTeamMode, bIsTeamMode)
	MAKE_BOOL_GETTERSETTER(CanTeamAttack, bCanTeamAttack)
#pragma endregion
	
private:
	
#pragma region --- Game.Color ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P1_Col;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P2_Col;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P3_Col;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P4_Col;
#pragma endregion

	
#pragma region --- Game.Online ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Online", meta=(AllowPrivateAccess="true"))
	bool bIsOnline;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Online", meta=(AllowPrivateAccess="true"))
	bool bIsHost;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Online", meta=(AllowPrivateAccess="true"))
	TArray<bool> ReadyArray;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Online", meta=(AllowPrivateAccess="true"))
	bool bIsReady;
#pragma endregion
	
#pragma region --- Game.Players ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ACharacter> Fighters;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<ECharacter> PlayerCharacters;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 PlayerNumber;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 NumberOfPlayers;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<AController*> PlayerControllers;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerNumberIDs;
	
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
	TArray<int32> PlayerPositions;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Score;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> AliveArray;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> CPU;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerTeam;
#pragma endregion
	
#pragma region --- Game.Loop ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 StockCount;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 Min;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	bool bIsLoopEnabled;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	EGameModes MainGameMode;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	EInGameModes SubGameMode;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	bool bIsGameOver;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 NumPlayersAlive;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 WinnerPlayerID;
#pragma endregion
	
#pragma region --- Game.Menu ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Menu", meta=(AllowPrivateAccess="true"))
	TArray<bool> ActiveControllers;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Menu", meta=(AllowPrivateAccess="true"))
	EMenus Menus;
#pragma endregion
	
#pragma region --- Developer.Debug ---
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bIsDebugMode;
	
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bShowDamageBoxes;
	
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bShowStates;
#pragma endregion
	
#pragma region --- Game.Team ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Team", meta=(AllowPrivateAccess="true"))
	bool bIsTeamMode;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Team", meta=(AllowPrivateAccess="true"))
	bool bCanTeamAttack;
#pragma endregion
};