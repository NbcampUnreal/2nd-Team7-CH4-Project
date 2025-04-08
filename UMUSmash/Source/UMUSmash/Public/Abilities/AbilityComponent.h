

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseAbility> AbilityRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> DamageScale = { 1.f, 0.9f, 0.8f, 0.7f, 0.6f };
	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
	void MainTick();
	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
	void BufferCall(EBufferType BufferType);
private:
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
	UFUNCTION(BlueprintCallable)
	void AttachAbility();
	UFUNCTION(BlueprintCallable)
	void SpawnAbility(FAbility Ability);
	void ActivateAbility(TObjectPtr<ABaseAbility> Ability);
	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable)
	void Respawning();

	UFUNCTION(BlueprintCallable)
	void EndAllNonChargedAbilities(FAbility& Ability);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	TObjectPtr<ABaseCharacter> Parent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
	FAbility SpecialNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
	FAbility SpecialUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
	FAbility SpecialDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
	FAbility SpecialForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
	FAbility SuperAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tilt")
	FAbility TiltNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tilt")
	FAbility TiltUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tilt")
	FAbility TiltSide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tilt")
	FAbility TiltDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Air")
	FAbility AirUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Air")
	FAbility AirDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Air")
	FAbility AirForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Air")
	FAbility AirBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Air")
	FAbility AirNeutral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smash")
	FAbility SmashUp; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smash")
	FAbility SmashForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smash")
	FAbility SmashDown;

	FAbility TauntUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Taunt")
	FAbility TauntDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Taunt")
	FAbility TauntLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Taunt")
	FAbility TauntRight;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	FAbility DodgeAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	FAbility DodgeSpot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	FAbility DodgeBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	FAbility DodgeForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FAbility ThrowUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FAbility ThrowDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FAbility ThrowBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FAbility ThrowForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FAbility Pummel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FAbility Grab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FAbility UseItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FAbility ThrowItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	FAbility ExtraAbility1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	FAbility ExtraAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	FAbility ExtraAbility3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	FAbility ExtraAbility4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ledge")
	FAbility LedgeAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ledge")
	FAbility Ledge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prone")
	FAbility ProneStand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prone")
	FAbility ProneAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	FAbility DashAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	FAbility LadderAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	FAbility SwimAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	FAbility Respawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	FAbility LevelIntro;
};
