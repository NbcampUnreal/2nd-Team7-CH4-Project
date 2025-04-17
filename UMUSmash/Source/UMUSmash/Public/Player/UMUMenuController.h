

#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.h"
#include "GameFramework/PlayerController.h"
#include "UMUMenuController.generated.h"

class UHUDMenu;
class UHUDLobby;

UCLASS()
class UMUSMASH_API AUMUMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	void BlockClientInput();
	void SetUseCursor(const bool& bUseCursor);

	void ChangeNextProgressUI(EMenuWidgetState NextWidgetState);
	void UpdateCPUCount(const int32& NewValue);
	void UpdateCPUMaxCount(const int32& NewValue);
	void UpdateRuleCount(const int32& NewValue);
	void UpdateInGameMode(const EInGameModes NewInGameMode);
	
	
	
	// Getter & Setter
	TObjectPtr<UHUDMenu> GetHUDMenuInstance() const { return HUDMenuInstance; }
	TObjectPtr<UHUDLobby> GetHUDLobbyInstance() const { return HUDLobbyInstance; }
	void SetPlayerID(const int& NewPlayerID) { PlayerID = NewPlayerID; }
	int32 GetPlayerID() const { return PlayerID; }
	bool GetIsReady() const { return bIsReady; }
	


	// RPC
	UFUNCTION(Server, UnReliable)
	void ServerRPCSetCPUCount(const int32& NewCount);
	UFUNCTION(Server, UnReliable)
	void ServerRPCChangeRule(const EInGameModes& NewInGameMode);
	UFUNCTION(Server, UnReliable)
	void ServerRPCSetRuleCount(const int32& NewCount);
	UFUNCTION(Server, UnReliable)
	void ServerRPCSelectedCharacter(const ECharacter& SelectedCharacterValue);

protected:
	virtual void BeginPlay() override;

	void AddNumberOfPlayers();
	UFUNCTION()
	void OnRep_IsReady();
	
	void AddHUDMenu();
	void AddHUDLobby();
	void AddHUDWidget();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UHUDMenu> HUDMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TObjectPtr<UHUDMenu> HUDMenuInstance;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UHUDLobby> HUDLobbyClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TObjectPtr<UHUDLobby> HUDLobbyInstance;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 PlayerID;
	UPROPERTY(ReplicatedUsing = OnRep_IsReady, BlueprintReadOnly)
	bool bIsReady = false;
	UPROPERTY(Replicated, BlueprintReadOnly)
	ECharacter SelectedCharacter;
};
