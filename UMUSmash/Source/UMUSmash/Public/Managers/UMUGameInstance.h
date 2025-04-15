#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "Engine/GameInstance.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "UMUGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAliveCountChanged, int32, NewNumPlayersAlive);

UCLASS()
class UMUSMASH_API UUMUGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()



public:
	UFUNCTION(BlueprintCallable, Category="Game")
	void ServerTravel(const FString& MapName) const;
	
	bool IsGameOver() const;
	void SetIsGameOver(const bool& NewValue);


	// --- Game rule --- 
	UFUNCTION(BlueprintCallable, Category="Game.Players")
	void CheckGameOverConditions() const;
	UFUNCTION(BlueprintCallable)
	void BroadcastChangedAliveCount() const;
	

	
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
	MAKE_GETTERSETTER(int32, Seconds)
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

public:
	UPROPERTY(BlueprintAssignable)
	FOnAliveCountChanged OnAliveCountChanged;
	
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
	bool bIsOnline = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Online", meta=(AllowPrivateAccess="true"))
	bool bIsHost = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Online", meta=(AllowPrivateAccess="true"))
	TArray<bool> ReadyArray = {false};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Online", meta=(AllowPrivateAccess="true"))
	bool bIsReady = false;
#pragma endregion
	
#pragma region --- Game.Players ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ACharacter> Fighters = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<ECharacter> PlayerCharacters = {ECharacter::Fighter, ECharacter::Fighter, ECharacter::None, ECharacter::None};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 PlayerNumber = 1;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	int32 NumberOfPlayers = 1;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<AController*> PlayerControllers = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerNumberIDs = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Elims = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> SelfElim = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Falls = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageDone = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageTaken = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerPositions = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Score = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> AliveArray = {true, true, false, false};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> CPU = {false, false, false, false};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerTeam = {1, 2, 3, 4};
#pragma endregion
	
#pragma region --- Game.Loop ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 StockCount = 3;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 Min = 0;

	double Seconds = 0;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	bool bIsLoopEnabled = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	EGameModes MainGameMode = EGameModes::VS;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	EInGameModes SubGameMode = EInGameModes::Stock;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	bool bIsGameOver = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 NumPlayersAlive = 4;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Loop", meta=(AllowPrivateAccess="true"))
	int32 WinnerPlayerID = 0;
#pragma endregion
	
#pragma region --- Game.Menu ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Menu", meta=(AllowPrivateAccess="true"))
	TArray<bool> ActiveControllers = {};
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Menu", meta=(AllowPrivateAccess="true"))
	EMenus Menus = EMenus::Title;
#pragma endregion
	
#pragma region --- Developer.Debug ---
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bIsDebugMode = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bShowDamageBoxes = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Developer.Debug", meta=(AllowPrivateAccess="true"))
	bool bShowStates = false;
#pragma endregion
	
#pragma region --- Game.Team ---
	UPROPERTY(BlueprintReadWrite, Category="Game.Team", meta=(AllowPrivateAccess="true"))
	bool bIsTeamMode = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Game.Team", meta=(AllowPrivateAccess="true"))
	bool bCanTeamAttack = false;
#pragma endregion

#pragma region --- network.ip ---

	UFUNCTION(BlueprintCallable, Category = "Network")
	void HostGame(const FString& MapName);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinGame(const FString& MapName, const FString& HostCode);

	UFUNCTION(BlueprintCallable, Category = "Network")
	FString GetMyHostCode();


	FString PadLeft(const FString& Input, int32 TotalLength, TCHAR PadChar = '0') const;

	FString LocalIPToHostCode(const FString& IP) const;
	FString HostCodeToIP(const FString& Code) const;

	FString GetLocalIPAddress() const;

#pragma endregion
};