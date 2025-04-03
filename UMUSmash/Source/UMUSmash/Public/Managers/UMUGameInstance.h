#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UMUGameInstance.generated.h"

// Enum Definitions

UENUM(BlueprintType)
enum class ECharacter : uint8
{
	None		UMETA(DisplayName = "None"),
	Fighter		UMETA(DisplayName = "Fighter"),
	SwordMan	UMETA(DisplayName = "Sword Man"),
	Gunner		UMETA(DisplayName = "Gunner"),
	Hats		UMETA(DisplayName = "Hats"),
	Mage		UMETA(DisplayName = "Mage"),
	Unknown		UMETA(DisplayName = "^V^"),
	Bob			UMETA(DisplayName = "Bob"),
	Random		UMETA(DisplayName = "Random"),
};

UENUM(BlueprintType)
enum class EGameModes : uint8
{
	VS			UMETA(DisplayName = "VS"),
	Online		UMETA(DisplayName = "Online"),
	Arcade		UMETA(DisplayName = "Arcade"),
};

UENUM(BlueprintType)
enum class EInGameModes : uint8
{
	Stock		UMETA(DisplayName = "Stock"),
	Time		UMETA(DisplayName = "Time"),
	MiniGame	UMETA(DisplayName = "MiniGame"),
	BossFight	UMETA(DisplayName = "BossFight"),
};

UENUM(BlueprintType)
enum class EMenus : uint8
{
	Main				UMETA(DisplayName = "Main"),
	CharacterSelect		UMETA(DisplayName = "CharacterSelect"),
	MapSelect			UMETA(DisplayName = "MapSelect"),
	Online				UMETA(DisplayName = "Online"),
	Host				UMETA(DisplayName = "Host"),
	Join				UMETA(DisplayName = "Join"),
	Lobby				UMETA(DisplayName = "Lobby"),
	Title				UMETA(DisplayName = "Title"),
};


UCLASS()
class UMUSMASH_API UUMUGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OpenLevel(const FString& MapName) const;
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCClientsTravel(const FString& MapName);
	UFUNCTION(BlueprintNativeEvent)
	void ServerTravel(const FString& MapName);

	
	// Getter/Setter 함수 - Color region

	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE FSlateColor GetP1_Col() const { return P1_Col; }
	
	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE void SetP1_Col(const FSlateColor& NewColor) { P1_Col = NewColor; }

	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE FSlateColor GetP2_Col() const { return P2_Col; }
	
	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE void SetP2_Col(const FSlateColor& NewColor) { P2_Col = NewColor; }

	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE FSlateColor GetP3_Col() const { return P3_Col; }
	
	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE void SetP3_Col(const FSlateColor& NewColor) { P3_Col = NewColor; }

	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE FSlateColor GetP4_Col() const { return P4_Col; }
	
	UFUNCTION(BlueprintCallable, Category="Color")
	FORCEINLINE void SetP4_Col(const FSlateColor& NewColor) { P4_Col = NewColor; }

	// Getter/Setter 함수 - Online region

	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE bool IsOnline() const { return bOnline; }
	
	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE void SetOnline(const bool& bNewOnline) { bOnline = bNewOnline; }

	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE bool IsHost() const { return bIsHost; }
	
	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE void SetIsHost(const bool& bNewIsHost) { bIsHost = bNewIsHost; }

	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE TArray<bool> GetReadyArray() const { return ReadyArray; }
	
	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE void SetReadyArray(const TArray<bool>& NewReadyArray) { ReadyArray = NewReadyArray; }

	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE bool IsReady() const { return bIsReady; }
	
	UFUNCTION(BlueprintCallable, Category="Online")
	FORCEINLINE void SetIsReady(const bool& bNewIsReady) { bIsReady = bNewIsReady; }

	// Getter/Setter 함수 - Players region

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TSubclassOf<ACharacter> GetFighter() const { return Fighter; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetFighter(const TSubclassOf<ACharacter>& NewFighter) { Fighter = NewFighter; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<ECharacter> GetPlayerCharacters() const { return PlayerCharacters; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetPlayerCharacters(const TArray<ECharacter>& NewPlayerCharacters) { PlayerCharacters = NewPlayerCharacters; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<APlayerController*> GetPlayerControllers() const { return PlayerControllers; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetPlayerControllers(const TArray<APlayerController*>& NewPlayerControllers) { PlayerControllers = NewPlayerControllers; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE int32 GetPlayerNumber() const { return PlayerNumber; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetPlayerNumber(const int32& NewPlayerNumber) { PlayerNumber = NewPlayerNumber; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE int32 GetNumberOfPlayers() const { return NumberOfPlayers; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetNumberOfPlayers(const int32& NewNumberOfPlayers) { NumberOfPlayers = NewNumberOfPlayers; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetPlayerNumberIDs() const { return PlayerNumberIDs; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetPlayerNumberIDs(const TArray<int32>& NewPlayerNumberIDs) { PlayerNumberIDs = NewPlayerNumberIDs; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetElims() const { return Elims; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetElims(const TArray<int32>& NewElims) { Elims = NewElims; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetSelfElim() const { return SelfElim; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetSelfElim(const TArray<int32>& NewSelfElim) { SelfElim = NewSelfElim; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetFalls() const { return Falls; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetFalls(const TArray<int32>& NewFalls) { Falls = NewFalls; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetDamageDone() const { return DamageDone; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetDamageDone(const TArray<int32>& NewDamageDone) { DamageDone = NewDamageDone; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetDamageTaken() const { return DamageTaken; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetDamageTaken(const TArray<int32>& NewDamageTaken) { DamageTaken = NewDamageTaken; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetPlayerPositions() const { return PlayerPositions; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetPlayerPositions(const TArray<int32>& NewPlayerPositions) { PlayerPositions = NewPlayerPositions; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetScore() const { return Score; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetScore(const TArray<int32>& NewScore) { Score = NewScore; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<bool> GetAliveArray() const { return AliveArray; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetAliveArray(const TArray<bool>& NewAliveArray) { AliveArray = NewAliveArray; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<bool> GetCPU() const { return CPU; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetCPU(const TArray<bool>& NewCPU) { CPU = NewCPU; }

	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE TArray<int32> GetPlayerTeam() const { return PlayerTeam; }
	
	UFUNCTION(BlueprintCallable, Category="Players")
	FORCEINLINE void SetPlayerTeam(const TArray<int32>& NewPlayerTeam) { PlayerTeam = NewPlayerTeam; }

	// Getter/Setter 함수 - GameLoop region

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE int32 GetStockCount() const { return StockCount; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetStockCount(const int32& NewStockCount) { StockCount = NewStockCount; }

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE int32 GetMin() const { return Min; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetMin(const int32& NewMin) { Min = NewMin; }

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE bool IsGameLooped() const { return bIsGameLooped; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetIsGameLooped(const bool& bNewIsGameLooped) { bIsGameLooped = bNewIsGameLooped; }

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE EGameModes GetMainMode() const { return MainMode; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetMainMode(const EGameModes& NewMainMode) { MainMode = NewMainMode; }

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE EInGameModes GetSubMode() const { return SubMode; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetSubMode(const EInGameModes& NewSubMode) { SubMode = NewSubMode; }

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE bool IsEndGame() const { return bIsEndGame; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetIsEndGame(const bool& bNewIsEndGame) { bIsEndGame = bNewIsEndGame; }

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE int32 GetPlayersAlive() const { return PlayersAlive; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetPlayersAlive(const int32& NewPlayersAlive) { PlayersAlive = NewPlayersAlive; }

	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE int32 GetWinner() const { return Winner; }
	
	UFUNCTION(BlueprintCallable, Category="GameLoop")
	FORCEINLINE void SetWinner(const int32& NewWinner) { Winner = NewWinner; }

	// Getter/Setter 함수 - Menu region

	UFUNCTION(BlueprintCallable, Category="Menu")
	FORCEINLINE TArray<bool> GetActiveControllers() const { return ActiveControllers; }
	
	UFUNCTION(BlueprintCallable, Category="Menu")
	FORCEINLINE void SetActiveControllers(const TArray<bool>& NewActiveControllers) { ActiveControllers = NewActiveControllers; }

	UFUNCTION(BlueprintCallable, Category="Menu")
	FORCEINLINE EMenus GetMenus() const { return Menus; }
	
	UFUNCTION(BlueprintCallable, Category="Menu")
	FORCEINLINE void SetMenus(const EMenus& NewMenus) { Menus = NewMenus; }

	// Getter/Setter 함수 - Debug region

	UFUNCTION(BlueprintCallable, Category="Debug")
	FORCEINLINE bool IsDebugMode() const { return bIsDebugMode; }
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	FORCEINLINE void SetIsDebugMode(const bool& bNewIsDebugMode) { bIsDebugMode = bNewIsDebugMode; }

	UFUNCTION(BlueprintCallable, Category="Debug")
	FORCEINLINE bool GetShowDamageBoxes() const { return bShowDamageBoxes; }
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	FORCEINLINE void SetShowDamageBoxes(const bool& bNewShowDamageBoxes) { bShowDamageBoxes = bNewShowDamageBoxes; }

	UFUNCTION(BlueprintCallable, Category="Debug")
	FORCEINLINE bool GetShowStates() const { return bShowStates; }
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	FORCEINLINE void SetShowStates(const bool& bNewShowStates) { bShowStates = bNewShowStates; }

	// Getter/Setter 함수 - Team region

	UFUNCTION(BlueprintCallable, Category="Team")
	FORCEINLINE bool IsTeamMode() const { return bIsTeamMode; }
	
	UFUNCTION(BlueprintCallable, Category="Team")
	FORCEINLINE void SetIsTeamMode(const bool& bNewIsTeamMode) { bIsTeamMode = bNewIsTeamMode; }

	UFUNCTION(BlueprintCallable, Category="Team")
	FORCEINLINE bool CanTeamAttack() const { return bCanTeamAttack; }
	
	UFUNCTION(BlueprintCallable, Category="Team")
	FORCEINLINE void SetCanTeamAttack(const bool& bNewCanTeamAttack) { bCanTeamAttack = bNewCanTeamAttack; }

private:
#pragma region Color
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P1_Col;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P2_Col;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P3_Col;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Color", meta=(AllowPrivateAccess="true"))
	FSlateColor P4_Col;
#pragma endregion

#pragma region Online
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online", meta=(AllowPrivateAccess="true"))
	bool bOnline;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online", meta=(AllowPrivateAccess="true"))
	bool bIsHost;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online", meta=(AllowPrivateAccess="true"))
	TArray<bool> ReadyArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online", meta=(AllowPrivateAccess="true"))
	bool bIsReady;
#pragma endregion

#pragma region Players
	// BP 에서 TArray<BPFighter> Fighters 변수로 선언
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ACharacter> Fighter;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<ECharacter> PlayerCharacters;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<APlayerController*> PlayerControllers;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	int32 PlayerNumber;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	int32 NumberOfPlayers;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerNumberIDs;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Elims;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> SelfElim;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Falls;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageDone;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> DamageTaken;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerPositions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> AliveArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<bool> CPU;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Players", meta=(AllowPrivateAccess="true"))
	TArray<int32> PlayerTeam;
#pragma endregion

#pragma region GameLoop
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	int32 StockCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	int32 Min;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	bool bIsGameLooped;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	EGameModes MainMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	EInGameModes SubMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	bool bIsEndGame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	int32 PlayersAlive;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameLoop", meta=(AllowPrivateAccess="true"))
	int32 Winner;
#pragma endregion

#pragma region Menu
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Menu", meta=(AllowPrivateAccess="true"))
	TArray<bool> ActiveControllers;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Menu", meta=(AllowPrivateAccess="true"))
	EMenus Menus;
#pragma endregion

#pragma region Debug
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug", meta=(AllowPrivateAccess="true"))
	bool bIsDebugMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug", meta=(AllowPrivateAccess="true"))
	bool bShowDamageBoxes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug", meta=(AllowPrivateAccess="true"))
	bool bShowStates;
	#pragma endregion
	#pragma region Team
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Team", meta=(AllowPrivateAccess="true"))
	bool bIsTeamMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Team", meta=(AllowPrivateAccess="true"))
	bool bCanTeamAttack;
#pragma endregion
};
