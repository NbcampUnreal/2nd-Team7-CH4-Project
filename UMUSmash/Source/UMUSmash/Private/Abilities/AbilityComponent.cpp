#include "Abilities/AbilityComponent.h"
#include "Character\BaseCharacter.h"
#include "Abilities\BaseAbility.h"
#include "Net\UnrealNetwork.h"
#include "Character\CharStatComponent.h"
#include "Online/CoreOnline.h"


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
	case EBufferType::ItemUse:
		ItemUsed();
		break;
	case EBufferType::ItemThrow:
		ItemThrowed();
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
	case EAbilityType::UseItem:
		ItemUsed();
		break;
	case EAbilityType::ThrowItem:
		ItemThrowed();
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
		if (Parent->CharStatComponent->SuperGage >= 100)
		{
			Parent->CharStatComponent->SuperGage = 0;
			Parent->AttackType = EAttackType::Super;
			ActivateAbility(SuperAbility.Ability);
		}
		else
		{
			Parent->AttackType = EAttackType::SpecialNeutral;
			ActivateAbility(SpecialNeutral.Ability);
		}
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
void UAbilityComponent::ActivateAbility_Implementation(ABaseAbility* Ability)
{
	if (Ability == nullptr) return;
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

void UAbilityComponent::ItemUsed_Implementation()
{
	ActivateAbility(UseItemAbility.Ability);

}

void UAbilityComponent::ItemThrowed_Implementation()
{
	ActivateAbility(ThrowItemAbility.Ability);

}

void UAbilityComponent::AttachAbility_Implementation()
{
	if(GetOwner()->HasAuthority())
	//Basic
	SpawnAbility(TiltNeutral);
	SpawnAbility(TiltUp);
	SpawnAbility(TiltSide);
	SpawnAbility(TiltDown);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))
	//Special
	SpawnAbility(SpecialDown);
	SpawnAbility(SpecialForward);
	SpawnAbility(SpecialUp);
	SpawnAbility(SpecialNeutral);

	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))
	//Air
	SpawnAbility(AirUp);
	SpawnAbility(AirDown);
	SpawnAbility(AirForward);
	SpawnAbility(AirBack);
	SpawnAbility(AirNeutral);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))
	//Smash
	SpawnAbility(SmashUp);
	SpawnAbility(SmashForward);
	SpawnAbility(SmashDown);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))
	//Taunt
	SpawnAbility(TauntUp);
	SpawnAbility(TauntDown);
	SpawnAbility(TauntLeft);
	SpawnAbility(TauntRight);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))
	///Grab & Throw
	SpawnAbility(Grab);
	SpawnAbility(ThrowUp);
	SpawnAbility(ThrowDown);
	SpawnAbility(ThrowForward);
	SpawnAbility(ThrowBack);
	SpawnAbility(Pummel);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))
	//Dodge
	SpawnAbility(DodgeAir);
	SpawnAbility(DodgeSpot);
	SpawnAbility(DodgeBack);
	SpawnAbility(DodgeForward);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))
	//Other
	SpawnAbility(LedgeAttack);
	SpawnAbility(Ledge);
	SpawnAbility(ProneAttack);
	SpawnAbility(ProneStand);
	SpawnAbility(SuperAbility);
	SpawnAbility(DashAttack);
	SpawnAbility(ThrowItemAbility);
	SpawnAbility(UseItemAbility);
	SpawnAbility(Respawn);
	SpawnAbility(LevelIntro);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Ability"))

	/*SpawnAbility(UseItem);
	SpawnAbility(ThrowItem);*/


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
	DOREPLIFETIME(UAbilityComponent, Ledge);
	DOREPLIFETIME(UAbilityComponent, LedgeAttack);

	DOREPLIFETIME(UAbilityComponent, SmashUp);
	DOREPLIFETIME(UAbilityComponent, SmashDown);
	DOREPLIFETIME(UAbilityComponent, SmashForward);
	DOREPLIFETIME(UAbilityComponent, SuperAbility);

	DOREPLIFETIME(UAbilityComponent, TiltNeutral);
	DOREPLIFETIME(UAbilityComponent, TiltUp);
	DOREPLIFETIME(UAbilityComponent, TiltDown);
	DOREPLIFETIME(UAbilityComponent, TiltSide);

	DOREPLIFETIME(UAbilityComponent, AirUp);
	DOREPLIFETIME(UAbilityComponent, AirDown);
	DOREPLIFETIME(UAbilityComponent, AirForward);
	DOREPLIFETIME(UAbilityComponent, AirBack);

	DOREPLIFETIME(UAbilityComponent, TauntUp);
	DOREPLIFETIME(UAbilityComponent, TauntDown);
	DOREPLIFETIME(UAbilityComponent, TauntLeft);
	DOREPLIFETIME(UAbilityComponent, TauntRight);

		///Grab & Throw
		DOREPLIFETIME(UAbilityComponent, Grab);
	DOREPLIFETIME(UAbilityComponent, ThrowUp);
	DOREPLIFETIME(UAbilityComponent, ThrowDown);
	DOREPLIFETIME(UAbilityComponent, ThrowForward);
	DOREPLIFETIME(UAbilityComponent, ThrowBack);
	DOREPLIFETIME(UAbilityComponent, Pummel);

		//Dodge
		DOREPLIFETIME(UAbilityComponent, DodgeAir);
	DOREPLIFETIME(UAbilityComponent, DodgeSpot);
	DOREPLIFETIME(UAbilityComponent, DodgeBack);
	DOREPLIFETIME(UAbilityComponent, DodgeForward);

	DOREPLIFETIME(UAbilityComponent, SpecialDown);
	DOREPLIFETIME(UAbilityComponent, SpecialForward);
	DOREPLIFETIME(UAbilityComponent, SpecialUp);
	DOREPLIFETIME(UAbilityComponent, SpecialNeutral);
	DOREPLIFETIME(UAbilityComponent, TauntUp);
	DOREPLIFETIME(UAbilityComponent, TauntDown);
	DOREPLIFETIME(UAbilityComponent, TauntLeft);
	DOREPLIFETIME(UAbilityComponent, TauntRight);

}

void FAbility::ActivateAbility()
{
	if (Ability)
	{
		Ability->bIsActive = true;
	}
}
