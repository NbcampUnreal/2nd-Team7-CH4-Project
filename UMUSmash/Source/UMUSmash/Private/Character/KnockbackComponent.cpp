#include "Character/KnockbackComponent.h"
#include "Character\BaseCharacter.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Character\CharStatComponent.h"
#include "Abilities\AbilityComponent.h"

// Sets default values for this component's properties
UKnockbackComponent::UKnockbackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKnockbackComponent::BeginPlay()
{
	Super::BeginPlay();
	Parent = Cast<ABaseCharacter>(GetOwner());
	// ...
	
}

void UKnockbackComponent::CharacterKnockback(EInputDirection Direction, float Angle)
{
	Parent->JumpNumber = 1;
	UCharacterMovementComponent* Movement = Parent->GetCharacterMovement();	
	Movement->SetMovementMode(EMovementMode::MOVE_Falling);
	FuncNockbackCalculation();
}

float UKnockbackComponent::FuncNockbackCalculation()
{
	int32 Percent = Parent->CharStatComponent->Percent;
	float Weight = (200 / (Parent->CharStatComponent->Weight + 100) * 1.4f);
	float DamageScale = Parent->AbilityComponent->DamageScale[Parent->AbilityComponent->UsedMoveCount];
	float Knockback = ((Parent->AttackDamage * Percent) / 20);
	Knockback += (Percent / 10);
	Knockback *= DamageScale;
	Knockback *= Weight;
	Knockback += 18;
	Knockback *= (Percent / 7) * Parent->HitScale;
	

	return Knockback;
}



