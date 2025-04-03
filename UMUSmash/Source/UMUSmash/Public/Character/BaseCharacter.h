

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FInputActionValue;

UENUM(BlueprintType)
enum class EFaceDirection : uint8
{
	Left,
	Right,
};

UENUM(BlueprintType)
enum class EInputDirection : uint8
{
	Up,
	Down,
	Back,
	Forward,
	None
};

UENUM(BlueprintType)
enum class EPlayerStateType : uint8
{
	Idle,
	Move,
	Crouch,
	Sprint,
	Jump,
	Fall,
	Hit,
	Launch,
	Ledge,
	Dead,
	Shield,
	Tumble,
	ShieldTumble,
	Prone,
	Stun,
	Dizzy,
	Ability,
	Dodge,
	FreeFall,
	Held,
	Hold
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	None,
	TiltUp,
	TiltDown,
	TiltForward,
	TiltBack,
	TiltNuetral,
	AirUp,
	AirDown,
	AirForward,
	AirBack,
	AirNuetral,
	SmashUp,
	SmashDown,
	SmashForward,
	SmashBack,
	SpecialUp,
	SpecialDown,
	SpecialForward,
	SpecialBack,
	SpecialNuetral,
	Grab,
	ThorwUp,
	ThorwDown,
	ThorwForward,
	ThorwBack,
	Pumble,
	LedgeAttack,
	ProneAttack,
	DodgeSpot,
	DodgeAir,
	DodgeBack,
	DodgeForard,
	Super
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None,
	Basic,
	Special,
	Air,
	Smash,
	Super,
	Dodge,
	Taunt,
	Ledge,
	Throw,
	Prone,
	Grab,
	Other
};

UCLASS()
class UMUSMASH_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	float PlayerAcceleration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	int32 JumpCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	bool bCanMove = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bCanJump = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	EFaceDirection FaceDirection = EFaceDirection::Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	bool bCanFlip = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	float LeftRight = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	float UpDown = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	EInputDirection Direction = EInputDirection::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	float ZPos = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	float YPos = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	float FootZPos = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	FVector Location = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	FVector LocationFeet = FVector(0, 0, 0);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "States")
	EPlayerStateType CharState = EPlayerStateType::Idle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "States")
	EAttackType AttackType = EAttackType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "States")
	EAbilityType AbilityType = EAbilityType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "States")
	EInputDirection DirectionType = EInputDirection::None;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
