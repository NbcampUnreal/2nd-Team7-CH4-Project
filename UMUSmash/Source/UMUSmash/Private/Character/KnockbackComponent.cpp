#include "Character/KnockbackComponent.h"
#include "Character\BaseCharacter.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Character\CharStatComponent.h"
#include "Abilities\AbilityComponent.h"
#include "Components\CapsuleComponent.h"
#include "Character\WallBounceComponent.h"

// Sets default values for this component's properties
UKnockbackComponent::UKnockbackComponent()
{

}


// Called when the game starts
void UKnockbackComponent::BeginPlay()
{
	Super::BeginPlay();
	Parent = Cast<ABaseCharacter>(GetOwner());
	ParentCapsuleComp = Parent->GetCapsuleComponent();
	// ...
	
}

void UKnockbackComponent::CharacterKnockback(EFaceDirection Direction, float Angle, float Stun,float BaseKockback)
{
	Parent->JumpNumber = 1;
	UCharacterMovementComponent* Movement = Parent->GetCharacterMovement();	
	Movement->SetMovementMode(EMovementMode::MOVE_Falling);
	FVector CapsuleLocation = ParentCapsuleComp->GetComponentLocation();
	CapsuleLocation.Z += 20;
	ParentCapsuleComp->SetWorldLocation(CapsuleLocation, false, nullptr, ETeleportType::TeleportPhysics);
	float Knockback = FuncNockbackCalculation()+ BaseKockback;
	if (Knockback > LaunchThreshold)
	{
		Parent->PlayerStateType = EPlayerStateType::launch;
	}
	FRotator Rotator = FRotator(Angle, 0, 0);
	FVector UpVector = ((FRotationMatrix(Rotator).GetUnitAxis(EAxis::Z)).GetSafeNormal(0.0001f)) * Knockback;
	FVector LaunchVector = FVector(UpVector.X, UpVector.Z, UpVector.Y);
	if (Direction == EFaceDirection::Right)
	{
		LaunchVector.Y *= -1;
	}
	Parent->LaunchCharacter(LaunchVector, false, false);
	if (Parent->PlayerStateType == EPlayerStateType::launch)
	{
		GetWorld()->GetTimerManager().SetTimer(KnockbackDelayTimer,
			[this]
			{
				Parent->PlayerStateType = EPlayerStateType::tumble;
			},
			Knockback / 2000,
			false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(KnockbackDelayTimer,
			[this]
			{
				Parent->PlayerStateType = EPlayerStateType::stun;
			},
			Stun,
			false);
	}
}

float UKnockbackComponent::FuncNockbackCalculation()
{
	int32 Percent = Parent->CharStatComponent->Percent;
	float Weight = (200 / (Parent->CharStatComponent->Weight + 100)) * 1.4f;
	float DamageScale = Parent->AbilityComponent->DamageScale[Parent->AbilityComponent->UsedMoveCount];
	float Knockback = ((Parent->AttackDamage * Percent) / 20);
	Knockback += (Percent / 10);
	Knockback *= DamageScale;
	Knockback *= Weight;
	Knockback += 18;
	Knockback *= (Percent / 7) * Parent->HitScale;
	Knockback += 1000;

	return Knockback;
}

void UKnockbackComponent::LaunchBounce(FVector LaunchVector)
{
	FHitResult OutHit;
	FVector StartPos = ParentCapsuleComp->GetComponentLocation();
	FVector EndPos = StartPos;
	EndPos.Z = -120;
	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		OutHit,
		StartPos,
		EndPos,
		ECollisionChannel::ECC_Visibility,
		Params
	);
	if (bHit && LaunchVector.Z < 0)
	{
		Parent->BounceVector = LaunchVector;
	}
	Parent->InputDirection = EInputDirection::Down;
	Parent->PlayerStateType = EPlayerStateType::launch;
	Parent->WallBounceComponent->WallBounce();
}



