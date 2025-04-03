


#include "Character/Ability.h"
#include "Character\BaseCharacter.h"
// Sets default values for this component's properties
UAbility::UAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbility::BeginPlay()
{
	Super::BeginPlay();


	Parent = Cast<ABaseCharacter>(GetOwner());
	check(Parent != nullptr);
	// ...
	
}

void UAbility::MainTick()
{
	if (Parent->CharState == EPlayerStateType::Ability && Parent->AttackType == EAttackType::None)
	{
		SwitchOnAbilityType();
	}
}

void UAbility::SwitchOnAbilityType()
{
	switch (Parent->AbilityType)
	{
	case EAbilityType::None:
		break;
	case EAbilityType::Basic:
		BasicAttack();
		break;
	case EAbilityType::Special:
		SpecialAttack();
		break;
	case EAbilityType::Air:
		AirAttack();
		break;
	case EAbilityType::Smash:
		SmashAttack();
		break;
	case EAbilityType::Super:
		break;
	case EAbilityType::Dodge:
		Dodge();
		break;
	case EAbilityType::Taunt:
		Taunt();
		break;
	case EAbilityType::Ledge:
		break;
	case EAbilityType::Throw:
		Throw();
		break;
	case EAbilityType::Prone:
		Prone();
		break;
	case EAbilityType::Grab:
		break;
	case EAbilityType::Other:
		break;
	default:
		check(false);
		break;
	}
}

void UAbility::BasicAttack()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::None:
		Parent->AttackType = EAttackType::TiltNuetral;
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::TiltUp;
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::TiltDown;
		break;
	case EInputDirection::Back:
		Parent->AttackType = EAttackType::TiltBack;
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::TiltForward;
		break;
	}
}

void UAbility::SpecialAttack()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::None:
		Parent->AttackType = EAttackType::SpecialNuetral;
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::SpecialUp;
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::SpecialDown;
		break;
	case EInputDirection::Back:
		Parent->AttackType = EAttackType::SpecialBack;
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::SpecialForward;
		break;
	}
}

void UAbility::AirAttack()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::None:
		Parent->AttackType = EAttackType::AirNuetral;
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::AirUp;
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::AirDown;
		break;
	case EInputDirection::Back:
		Parent->AttackType = EAttackType::AirBack;
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::AirForward;
		break;
	}
}

void UAbility::SmashAttack()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::SmashUp;
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::SmashDown;
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::SmashForward;
		break;
	}
}

void UAbility::Dodge()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::Up:
		break;
	case EInputDirection::Down:
		break;
	case EInputDirection::Back:
		break;
	case EInputDirection::Forward:
		break;
	}
}

void UAbility::Taunt()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::Up:
		break;
	case EInputDirection::Down:
		break;
	case EInputDirection::Back:
		break;
	case EInputDirection::Forward:
		break;
	}
}

void UAbility::Throw()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::Up:
		break;
	case EInputDirection::Down:
		break;
	case EInputDirection::Back:
		break;
	case EInputDirection::Forward:
		break;
	}
}

void UAbility::Prone()
{
	switch (Parent->DirectionType)
	{
	case EInputDirection::Up:
		break;
	case EInputDirection::Down:
		break;
	}
}





// Called every frame
void UAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

