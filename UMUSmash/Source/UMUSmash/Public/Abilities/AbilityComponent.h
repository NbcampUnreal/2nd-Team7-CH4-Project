

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
	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
	void MainTick();
	void BufferCall(EBufferType BufferType);
private:
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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	TObjectPtr<ABaseCharacter> Parent;
	UPROPERTY(EditAnywhere, Category = "Special")
	FAbility SpecialNeutral;
	UPROPERTY(EditAnywhere, Category = "Special")
	FAbility SpecialUp;
	UPROPERTY(EditAnywhere, Category = "Special")
	FAbility SpecialDown;
	UPROPERTY(EditAnywhere, Category = "Special")
	FAbility SpecialForward;
	UPROPERTY(EditAnywhere, Category = "Special")
	FAbility SuperAbility;

	UPROPERTY(EditAnywhere, Category = "Tilt")
	FAbility TiltNeutral;
	UPROPERTY(EditAnywhere, Category = "Tilt")
	FAbility TiltUp;
	UPROPERTY(EditAnywhere, Category = "Tilt")
	FAbility TiltSide;
	UPROPERTY(EditAnywhere, Category = "Tilt")
	FAbility TiltDown;

	UPROPERTY(EditAnywhere, Category = "Air")
	FAbility AirUp;
	UPROPERTY(EditAnywhere, Category = "Air")
	FAbility AirDown;
	UPROPERTY(EditAnywhere, Category = "Air")
	FAbility AirForward;
	UPROPERTY(EditAnywhere, Category = "Air")
	FAbility AirBack;
	UPROPERTY(EditAnywhere, Category = "Air")
	FAbility AirNeutral;

	UPROPERTY(EditAnywhere, Category = "Smash")
	FAbility SmashUp;
	UPROPERTY(EditAnywhere, Category = "Smash")
	FAbility SmashForward;
	UPROPERTY(EditAnywhere, Category = "Smash")
	FAbility SmashDown;

	FAbility TauntUp;
	UPROPERTY(EditAnywhere, Category = "Taunt")
	FAbility TauntDown;
	UPROPERTY(EditAnywhere, Category = "Taunt")
	FAbility TauntLeft;
	UPROPERTY(EditAnywhere, Category = "Taunt")
	FAbility TauntRight;


	UPROPERTY(EditAnywhere, Category = "Dodge")
	FAbility DodgeAir;
	UPROPERTY(EditAnywhere, Category = "Dodge")
	FAbility DodgeSpot;
	UPROPERTY(EditAnywhere, Category = "Dodge")
	FAbility DodgeBack;
	UPROPERTY(EditAnywhere, Category = "Dodge")
	FAbility DodgeForward;

	UPROPERTY(EditAnywhere, Category = "Throw")
	FAbility ThrowUp;
	UPROPERTY(EditAnywhere, Category = "Throw")
	FAbility ThrowDown;
	UPROPERTY(EditAnywhere, Category = "Throw")
	FAbility ThrowBack;
	UPROPERTY(EditAnywhere, Category = "Throw")
	FAbility ThrowForward;
	UPROPERTY(EditAnywhere, Category = "Throw")
	FAbility Pummel;
	UPROPERTY(EditAnywhere, Category = "Throw")
	FAbility Grab;

	UPROPERTY(EditAnywhere, Category = "Item")
	FAbility UseItem;
	UPROPERTY(EditAnywhere, Category = "Item")
	FAbility ThrowItem;

	UPROPERTY(EditAnywhere, Category = "Extra")
	FAbility ExtraAbility1;
	UPROPERTY(EditAnywhere, Category = "Extra")
	FAbility ExtraAbility2;
	UPROPERTY(EditAnywhere, Category = "Extra")
	FAbility ExtraAbility3;
	UPROPERTY(EditAnywhere, Category = "Extra")
	FAbility ExtraAbility4;

	UPROPERTY(EditAnywhere, Category = "Ledge")
	FAbility LedgeAttack;
	UPROPERTY(EditAnywhere, Category = "Ledge")
	FAbility Ledge;

	UPROPERTY(EditAnywhere, Category = "Prone")
	FAbility ProneStand;
	UPROPERTY(EditAnywhere, Category = "Prone")
	FAbility ProneAttack;

	UPROPERTY(EditAnywhere, Category = "Other")
	FAbility DashAttack;
	UPROPERTY(EditAnywhere, Category = "Other")
	FAbility LadderAttack;
	UPROPERTY(EditAnywhere, Category = "Other")
	FAbility SwimAttack;
	UPROPERTY(EditAnywhere, Category = "Other")
	FAbility Respawn;
};
