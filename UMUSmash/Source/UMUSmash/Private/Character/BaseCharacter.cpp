#include "Character/BaseCharacter.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Character\UMUPlayerController.h"
#include "Abilities\AbilityComponent.h"
#include "Character\LedgeComponent.h"
#include "Character\CharStatComponent.h"
#include "Character\KnockbackComponent.h"
#include "Character\WallBounceComponent.h"
#include "Character\FootStepComp.h"
#include <Net\UnrealNetwork.h>
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	LedgeComponent = CreateDefaultSubobject<ULedgeComponent>(TEXT("LedgeComponent"));
	CharStatComponent = CreateDefaultSubobject<UCharStatComponent>(TEXT("CharStatComponent"));
	KnockbackComponent = CreateDefaultSubobject<UKnockbackComponent>(TEXT("KnockbackComponent"));
	WallBounceComponent = CreateDefaultSubobject<UWallBounceComponent>(TEXT("WallBounceComponent"));
	FootStepComponent = CreateDefaultSubobject<UFootStepComp>(TEXT("FootStepComponent"));
}

void ABaseCharacter::ClearBuffer()
{
	BufferMove = EBufferType::None;
	BufferDirection = EInputDirection::None;
	bBufferdInput = false;
	bBufferdDirection = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, JumpNumber);
	DOREPLIFETIME(ABaseCharacter, Bounce);
	DOREPLIFETIME(ABaseCharacter, HorizontalInputValue);
	DOREPLIFETIME(ABaseCharacter, VerticalInputValue);
	DOREPLIFETIME(ABaseCharacter, JumpBuffer)
}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearAllTimersForObject(this);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AUMUPlayerController* PlayerController = Cast<AUMUPlayerController>(GetController()))
		{
			EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Started, this, &ABaseCharacter::StartJump);
			EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Canceled, this, &ABaseCharacter::EndJump);
			EnhancedInput->BindAction(PlayerController->VerticalInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::VerticalInputFunc);
			EnhancedInput->BindAction(PlayerController->HorizontalInputAction, ETriggerEvent::Triggered, this, &ABaseCharacter::HorizontalInputFunc);
	/*		EnhancedInput->BindAction(PlayerController->CrouchAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
			EnhancedInput->BindAction(PlayerController->AttackAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
			EnhancedInput->BindAction(PlayerController->SmashAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
			EnhancedInput->BindAction(PlayerController->ShieldAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
			EnhancedInput->BindAction(PlayerController->DodgeAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);*/
		}
	}
}

void ABaseCharacter::HorizontalInputFunc(const FInputActionValue& value)
{
	if (!CanMove) return;
	HorizontalInputValue = value.Get<float>();
	FlipFace();
	AddMovementInput(FVector(0, -1, 0), HorizontalInputValue, false);
	FootStepComponent->ProcessDualFeet(HorizontalInputValue);
	if (PlayerStateType == EPlayerStateType::Idle && !Pushed)
	{
		if (HorizontalInputValue != 0)
		{
			PlayerStateType = EPlayerStateType::walkrun;
		}
	}
}

void ABaseCharacter::VerticalInputFunc(const FInputActionValue& value)
{
	VerticalInputValue = value.Get<float>();
	if (VerticalInputValue < -0.9f)
	{
		if (GetMovementComponent()->IsFalling())
		{
			FastFall();
		}
		else
		{
			DropFromPlatforms();
		}
	}
}

void ABaseCharacter::FastFall()
{
	LaunchCharacter(FVector(0, 0, -1000), false, true);
}

void ABaseCharacter::FlipFace()
{
	if (!CanFilp) return;

	const bool bIgnoreVerticalInput = FMath::IsNearlyZero(VerticalInputValue, 0.5f);
	if (!bIgnoreVerticalInput) return;

	if (HorizontalInputValue > 0.f)
	{
		Faceing = EFaceDirection::Right;
	}
	else if (HorizontalInputValue < 0.f)
	{
		Faceing = EFaceDirection::Left;
	}
}

void ABaseCharacter::FaceCheck()
{
	FaceCheck_Multicast();
	FaceCheck_Server();
}

void ABaseCharacter::FaceCheck_Multicast_Implementation()
{
	RotateDirection(CanFilp);
}

void ABaseCharacter::FaceCheck_Server_Implementation()
{
	RotateDirection(CanFilp);
}

void ABaseCharacter::RotateDirection(const bool& Filp)
{
	if (Filp)
	{
		float Z = 0;
		switch (Faceing)
		{
		case EFaceDirection::Left:
			Z = 90;
			break;

		case EFaceDirection::Right:
			Z = -90;
			break;
		}
		SetActorRotation(FRotator(0, 0, Z), ETeleportType::TeleportPhysics);
	}
}

void ABaseCharacter::DropFromPlatforms()
{
	PlatPhaze = true;
	GetWorldTimerManager().SetTimer(DropFormPlatformsTimer,
		[this]
		{
			PlatPhaze = true;
		},
		0.15f,
		false);
}

void ABaseCharacter::StartJump()
{
	JumpButton = true;
	GetWorldTimerManager().SetTimer(JumpTimer, this, &ABaseCharacter::Jumping, JumpBuffer, false);
}

void ABaseCharacter::Jumping()
{
	if (JumpNumber > JumpMaxCount || !CanPlayerJump) return;
	
	FaceCheck();

	const bool bIgnoreHorizontalInput = FMath::IsNearlyZero(HorizontalInputValue, 0.3f);
	if (bIgnoreHorizontalInput)
	{
		GetMovementComponent()->StopMovementImmediately();
	}
	else
	{
		if (PlayerStateType != EPlayerStateType::sprint)
		{
			GetMovementComponent()->StopMovementImmediately();
			FVector LaunchVector = FVector::ZeroVector;
			if (HorizontalInputValue < 0)
				LaunchVector.Y = 500;
			else 
				LaunchVector.Y = -500;
			LaunchCharacter(LaunchVector, false, false);
		}
	}
	//GetMovementComponent()->Movement
}

void ABaseCharacter::EndJump()
{
	JumpButton = false;
	StopJumping();
}

