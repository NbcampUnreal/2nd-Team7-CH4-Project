

#pragma once

#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class ABaseCharacter;
class ABaseAbility;

USTRUCT(BlueprintType)
struct FAbility
{
	GENERATED_BODY()

public:
	void ActivateAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseAbility> AbilityClass;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABaseAbility> Ability;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UsedMoveCount = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<float> DamageScale = { 1.f, 0.9f, 0.8f, 0.7f, 0.6f };

	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
	void MainTick();

	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
	void BufferCall(EBufferType BufferType);

	//public -> protected -> private || 함수 -> 변수
private:
	UPROPERTY()
	TArray<TObjectPtr<ABaseAbility>> Abilities;
	FTimerHandle ResetMoveCountTimer;
	void ResetMoveCount();
	UFUNCTION(NetMulticast, Reliable)
	void WitchAbility();

	UFUNCTION(NetMulticast, Reliable)
	void BasicAttack();

	UFUNCTION(NetMulticast, Reliable)
	void SpecialAttack();

	UFUNCTION(NetMulticast, Reliable)
	void AirAttack();

	UFUNCTION(NetMulticast, Reliable)
	void SmashAttack();

	UFUNCTION(NetMulticast, Reliable)
	void Dodge();

	UFUNCTION(NetMulticast, Reliable)
	void Taunt();

	UFUNCTION(NetMulticast, Reliable)
	void Throw();

	UFUNCTION(NetMulticast, Reliable)
	void Prone();

	UFUNCTION(NetMulticast, Reliable)
	void ItemUsed();

	UFUNCTION(NetMulticast, Reliable)
	void ItemThrowed();


	UFUNCTION(BlueprintCallable)
	void AttachAbility();
	UFUNCTION(BlueprintCallable)
	void SpawnAbility(FAbility& Ability);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void ActivateAbility(ABaseAbility* Ability);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Respawning();

	UFUNCTION(BlueprintCallable)
	void EndAllNonChargedAbilities(const ABaseAbility* Ability);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:

	// TMap Key: Name, Value: Ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TMap<FName, FAbility> SpecialAbilityMap;
	UPROPERTY(BlueprintReadWrite, Replicated)
	TObjectPtr<ABaseCharacter> Parent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Special")
	FAbility SpecialNeutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Special")
	FAbility SpecialUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Special")
	FAbility SpecialDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Special")
	FAbility SpecialForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Special")
	FAbility SuperAbility;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Tilt")
	FAbility TiltNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Tilt")
	FAbility TiltUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Tilt")
	FAbility TiltSide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Tilt")
	FAbility TiltDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Air")
	FAbility AirUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Air")
	FAbility AirDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Air")
	FAbility AirForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Air")
	FAbility AirBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Air")
	FAbility AirNeutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Smash")
	FAbility SmashUp; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Smash")
	FAbility SmashForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Smash")
	FAbility SmashDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Taunt")
	FAbility TauntUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Taunt")
	FAbility TauntDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Taunt")
	FAbility TauntLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Taunt")
	FAbility TauntRight;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Dodge")
	FAbility DodgeAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Dodge")
	FAbility DodgeSpot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Dodge")
	FAbility DodgeBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Dodge")
	FAbility DodgeForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Throw")
	FAbility ThrowUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Throw")
	FAbility ThrowDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Throw")
	FAbility ThrowBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Throw")
	FAbility ThrowForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Throw")
	FAbility Pummel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Throw")
	FAbility Grab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item")
	FAbility UseItemAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Item")
	FAbility ThrowItemAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Extra")
	FAbility ExtraAbility1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Extra")
	FAbility ExtraAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Extra")
	FAbility ExtraAbility3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Extra")
	FAbility ExtraAbility4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Ledge")
	FAbility LedgeAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Ledge")
	FAbility Ledge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Prone")
	FAbility ProneStand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Prone")
	FAbility ProneAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Other")
	FAbility DashAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Other")
	FAbility LadderAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Other")
	FAbility SwimAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Other")
	FAbility Respawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Other")
	FAbility LevelIntro;
};
