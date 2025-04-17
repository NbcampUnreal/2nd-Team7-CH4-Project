

#pragma once

#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FInputActionValue;
class ABaseAbility;
class UAbilityComponent;
class ULedgeComponent;
class UCharStatComponent;
class UWallBounceComponent;
class UKnockbackComponent;
class UFootStepComp;

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

	UFUNCTION()
	void HorizontalInputFunc(const FInputActionValue& value);

	UFUNCTION()
	void VerticalInputFunc(const FInputActionValue& value);

	UFUNCTION()
	void FastFall();

	UFUNCTION()
	void FlipFace();

	UFUNCTION()
	void FaceCheck();

	UFUNCTION(NetMulticast, Reliable)
	void FaceCheck_Multicast();

	UFUNCTION(Server, Reliable)
	void FaceCheck_Server();

	UFUNCTION()
	void RotateDirection(const bool& Filp);

	UFUNCTION()
	void DropFromPlatforms();

	UFUNCTION(BlueprintImplementableEvent)
	void StartJump();

	UFUNCTION(BlueprintImplementableEvent)
	void EndJump();


//asdf
protected:
	// Called when the game starts or when spawned
	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void StartAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void EndAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void StartSmash();

	UFUNCTION(BlueprintImplementableEvent)
	void EndSmash();

	UFUNCTION(BlueprintImplementableEvent)
	void StartShield();

	UFUNCTION(BlueprintImplementableEvent)
	void EndShield();

	UFUNCTION(BlueprintImplementableEvent)
	void ItemPickUp();

	UFUNCTION(BlueprintImplementableEvent)
	void ItemPickEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void ItemThrow();


	UFUNCTION(BlueprintImplementableEvent)
	void ItemUse();

	UFUNCTION(BlueprintImplementableEvent)
	void ItemUseEnd();

	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HitScale = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerNo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int JumpNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool Bounce = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WallDetection = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Pushed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanFilp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlatPhaze = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool JumpButton = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanPlayerJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	double VerticalInputValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	double HorizontalInputValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	double JumpBuffer = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BounceVector = FVector::Zero();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool HasItem=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PickUpItem = false;


#pragma region Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilityComponent> AbilityComponent = nullptr;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULedgeComponent> LedgeComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCharStatComponent> CharStatComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWallBounceComponent> WallBounceComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UKnockbackComponent> KnockbackComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UFootStepComp> FootStepComponent = nullptr;

#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LedgeLocation = FVector::ZeroVector;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	EPlayerStateType PlayerStateType = EPlayerStateType::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType AttackType = EAttackType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityType AbilityType = EAbilityType::none;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputDirection InputDirection = EInputDirection::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFaceDirection Faceing = EFaceDirection::Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHitStateType HitStates = EHitStateType::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType EquipItemType = EItemType::None;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBufferdInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBufferdDirection = false;

	FTimerHandle DropFormPlatformsTimer;

	FTimerHandle JumpTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBufferType BufferMove = EBufferType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputDirection BufferDirection = EInputDirection::None;
};
