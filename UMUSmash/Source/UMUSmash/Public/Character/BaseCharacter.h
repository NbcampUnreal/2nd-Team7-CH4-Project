

#pragma once

#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FInputActionValue;
class ABaseAbility;
class UAbilityComponent;
class ULedgeComponent;

UCLASS()
class UMUSMASH_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	void ClearBuffer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAbilityParent(ABaseAbility* Ability);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//void Move(const FInputActionValue& value);
	//void Attack();
	//void Smash();
	//void Shield();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerNo = 0;
#pragma region Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilityComponent> AbilityComponent = nullptr;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULedgeComponent> LedgeComponent = nullptr;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LedgeLocation = FVector::ZeroVector;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerStateType PlayerStateType = EPlayerStateType::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType AttackType = EAttackType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityType AbilityType = EAbilityType::none;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputDirection InputDirection = EInputDirection::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHitStateType HitStates = EHitStateType::Normal;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBufferdInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBufferdDirection = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBufferType BufferMove = EBufferType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputDirection BufferDirection = EInputDirection::None;
};
