#include "Abilities/AbilityComponent.h"
#include "Character\BaseCharacter.h"
#include "Abilities\BaseAbility.h"
#include "Net\UnrealNetwork.h"


// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{

}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	Parent = Cast<ABaseCharacter>(GetOwner());
}

void UAbilityComponent::MainTick()
{
	if (Parent->PlayerStateType == EPlayerStateType::ability &&
		Parent->AttackType == EAttackType::None)
	{
		WitchAbility();
	}
}

void UAbilityComponent::BufferCall(const EBufferType BufferType)
{
	switch (BufferType)
	{
	case EBufferType::Attack:
		BasicAttack();
		break;
	case EBufferType::Special:
		SpecialAttack();
		break;
	case EBufferType::Jump:
		break;
	case EBufferType::Shield:
		break;
	case EBufferType::None:
		break;
	default:
		break;
	}
}

void UAbilityComponent::ResetMoveCount()
{
	UsedMoveCount = 0;	
}

void UAbilityComponent::WitchAbility_Implementation()
{
	check(Parent);
	switch (Parent->AbilityType)
	{
	case EAbilityType::none:
		break;
	case EAbilityType::Basic:
		BasicAttack();
		break;
	case EAbilityType::special:
		SpecialAttack();
		break;
	case EAbilityType::air:
		AirAttack();
		break;
	case EAbilityType::smash:
		SmashAttack();
		break;
	case EAbilityType::Super:
		break;
	case EAbilityType::other:
		DashAttack.Ability->bIsActive = true;
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
	case EAbilityType::grab:
		Grab.Ability->bIsActive = true;
		break;
	default:
		break;
	}
}

void UAbilityComponent::BasicAttack_Implementation()
{
	check(Parent);
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::TiltUp;
		ActivateAbility(TiltUp.Ability);
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::TiltDown;
		ActivateAbility(TiltDown.Ability);
		break;
	case EInputDirection::Back:
		Parent->AttackType = EAttackType::TiltBack;
		ActivateAbility(TiltSide.Ability);
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::TiltForward;
		ActivateAbility(TiltSide.Ability);
		break;
	case EInputDirection::None:
		Parent->AttackType = EAttackType::TiltNeutral;
		ActivateAbility(TiltNeutral.Ability);
		break;
	default:
		break;
	}
}

void UAbilityComponent::SpecialAttack_Implementation()
{
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::SpecialUp;
		ActivateAbility(SpecialUp.Ability);
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::SpecialDown;
		ActivateAbility(SpecialDown.Ability);
		break;
	case EInputDirection::Back:
		Parent->AttackType = EAttackType::SpecialBack;
		ActivateAbility(SpecialDown.Ability);
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::SpecialForward;
		ActivateAbility(SpecialForward.Ability);
		break;
	case EInputDirection::None:
		Parent->AttackType = EAttackType::SpecialNeutral;
		ActivateAbility(SpecialNeutral.Ability);
		break;
	default:
		break;
	}
}

void UAbilityComponent::AirAttack_Implementation()
{
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::AirUp;
		ActivateAbility(AirUp.Ability);
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::AirDown;
		ActivateAbility(AirDown.Ability);
		break;
	case EInputDirection::Back:
		Parent->AttackType = EAttackType::AirBack;
		ActivateAbility(AirBack.Ability);
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::AirForward;
		ActivateAbility(AirForward.Ability);
		break;
	case EInputDirection::None:
		Parent->AttackType = EAttackType::AirUp;
		ActivateAbility(AirUp.Ability);
		break;
	default:
		break;
	}
}

void UAbilityComponent::SmashAttack_Implementation()
{
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::SmashUp;
		ActivateAbility(SmashUp.Ability);	
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::SmashDown;
		ActivateAbility(SmashDown.Ability);
		break;
	case EInputDirection::Back:
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::SmashForward;
		ActivateAbility(SmashForward.Ability);
		break;
	case EInputDirection::None:
		break;
	default:
		break;
	}
}

void UAbilityComponent::Dodge_Implementation()
{
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		Parent->AttackType = EAttackType::DodgeAir;
		ActivateAbility(DodgeAir.Ability);
		break;
	case EInputDirection::Down:
		Parent->AttackType = EAttackType::DodgeSpot;
		ActivateAbility(DodgeSpot.Ability);
		break;
	case EInputDirection::Back:
		Parent->AttackType = EAttackType::DodgeBack;
		ActivateAbility(DodgeBack.Ability);
		break;
	case EInputDirection::Forward:
		Parent->AttackType = EAttackType::DodgeForward;
		ActivateAbility(DodgeForward.Ability);
		break;
	case EInputDirection::None:
		break;
	default:
		break;
	}
}

void UAbilityComponent::Taunt_Implementation()
{
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		ActivateAbility(TauntUp.Ability);
		break;
	case EInputDirection::Down:
		ActivateAbility(TauntDown.Ability);
		break;
	case EInputDirection::Back:
		ActivateAbility(TauntLeft.Ability);
		break;
	case EInputDirection::Forward:
		ActivateAbility(TauntRight.Ability);
		break;
	case EInputDirection::None:
		break;
	default:
		break;
	}
}

void UAbilityComponent::Throw_Implementation()
{
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		ActivateAbility(ThrowUp.Ability);
		break;
	case EInputDirection::Down:
		ActivateAbility(ThrowDown.Ability);
		break;
	case EInputDirection::Back:
		ActivateAbility(ThrowBack.Ability);
		break;
	case EInputDirection::Forward:
		ActivateAbility(ThrowForward.Ability);
		break;
	case EInputDirection::None:
		break;
	default:
		break;
	}
}

void UAbilityComponent::Prone_Implementation()
{
	switch (Parent->InputDirection)
	{
	case EInputDirection::Temp:
		break;
	case EInputDirection::Up:
		ActivateAbility(ProneStand.Ability);
		break;
	case EInputDirection::Down:
		ActivateAbility(ProneAttack.Ability);
		break;
	case EInputDirection::Back:
		break;
	case EInputDirection::Forward:
		break;
	case EInputDirection::None:
		break;
	default:
		break;
	}
}

void UAbilityComponent::SpawnAbility(FAbility& Ability)
{
	if (Ability.AbilityClass)
	{
		FVector SpawnLocation = Parent->GetActorLocation();
		FRotator SpawnRotation = Parent->GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Parent;
		SpawnParams.Instigator = Parent->GetInstigator();
		Ability.Ability = GetWorld()->SpawnActor<ABaseAbility>(Ability.AbilityClass, SpawnLocation, SpawnRotation, SpawnParams);
		Ability.Ability->AttachToActor(Parent, FAttachmentTransformRules::KeepRelativeTransform);
		Parent->SetAbilityParent(Ability.Ability);
		Abilities.Add(Ability.Ability);
	}
}
void UAbilityComponent::ActivateAbility(TObjectPtr<ABaseAbility> Ability)
{
	Ability->bIsActive = true;
	Parent->ClearBuffer();
	UsedMoveCount++;
	UsedMoveCount = FMath::Clamp(UsedMoveCount, 0, DamageScale.Num() - 1);
	GetWorld()->GetTimerManager().SetTimer(ResetMoveCountTimer, this, &UAbilityComponent::ResetMoveCount, 1.f, false);
}
void UAbilityComponent::Respawning_Implementation()
{
	if (Parent->PlayerStateType == EPlayerStateType::dead)
	{
		Respawn.Ability->bIsActive = true;
	}
}
void UAbilityComponent::AttachAbility()
{
	//Basic
	SpawnAbility(TiltNeutral);
	SpawnAbility(TiltUp);
	SpawnAbility(TiltSide);
	SpawnAbility(TiltDown);

	//Special
	SpawnAbility(SpecialDown);
	SpawnAbility(SpecialForward);
	SpawnAbility(SpecialUp);
	SpawnAbility(SpecialNeutral);

	//Air
	SpawnAbility(AirUp);
	SpawnAbility(AirDown);
	SpawnAbility(AirForward);
	SpawnAbility(AirBack);
	SpawnAbility(AirNeutral);

	//Smash
	SpawnAbility(SmashUp);
	SpawnAbility(SmashForward);
	SpawnAbility(SmashDown);
	
	//Taunt
	SpawnAbility(TauntUp);
	SpawnAbility(TauntDown);
	SpawnAbility(TauntLeft);
	SpawnAbility(TauntRight);

	///Grab & Throw
	SpawnAbility(Grab);
	SpawnAbility(ThrowUp);
	SpawnAbility(ThrowDown);
	SpawnAbility(ThrowForward);
	SpawnAbility(ThrowBack);
	SpawnAbility(Pummel);

	//Dodge
	SpawnAbility(DodgeAir);
	SpawnAbility(DodgeSpot);
	SpawnAbility(DodgeBack);
	SpawnAbility(DodgeForward);

	//Other
	SpawnAbility(LedgeAttack);
	SpawnAbility(Ledge);
	SpawnAbility(ProneAttack);
	SpawnAbility(ProneStand);
	SpawnAbility(SuperAbility);
	SpawnAbility(DashAttack);
	SpawnAbility(ThrowItem);
	SpawnAbility(UseItem);
	SpawnAbility(Respawn);
	SpawnAbility(LevelIntro);
	//Extra
	//SpawnAbility(ExtraAbility1);
	//SpawnAbility(ExtraAbility2);
	//SpawnAbility(ExtraAbility3);
	//SpawnAbility(ExtraAbility4);
}

void UAbilityComponent::EndAllNonChargedAbilities(const ABaseAbility* Ability)
{
	for (ABaseAbility* ForAbility : Abilities)
	{
		if (ForAbility->ChargeLevel == 0.f && Ability != ForAbility)
		{
			ForAbility->CallEndAbility();
		}
	}
}

void UAbilityComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAbilityComponent, Parent);
}

void FAbility::ActivateAbility()
{
	if (Ability)
	{
		Ability->bIsActive = true;
	}
}
