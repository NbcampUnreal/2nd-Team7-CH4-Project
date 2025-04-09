


#include "Character/LedgeComponent.h"
#include "Character\BaseCharacter.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Components\CapsuleComponent.h"
#include "Abilities\AbilityComponent.h"
#include "Abilities\BaseAbility.h"
#include <Net\UnrealNetwork.h>
// Sets default values for this component's properties
ULedgeComponent::ULedgeComponent()
{

}

void ULedgeComponent::BeginPlay()
{
	Super::BeginPlay();
	Parent = Cast<ABaseCharacter>(GetOwner());
}

void ULedgeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(LedgeGrabTimer);
}

void ULedgeComponent::LedgeGrab()
{
	check(Parent);
	Parent->HitStates = EHitStateType::Invincible;	
	UCharacterMovementComponent* CharacterMovement = Parent->GetCharacterMovement();
	CharacterMovement->StopMovementImmediately();
	Parent->LedgeLocation.Z -= 60;
	Parent->GetCapsuleComponent()->SetWorldLocation(Parent->LedgeLocation);
	CharacterMovement->GravityScale = 0.f;
	Parent->PlayerStateType = EPlayerStateType::ledge;
	Parent->AbilityComponent->Ledge.ActivateAbility();
	GetWorld()->GetTimerManager().SetTimer(LedgeGrabTimer, 
		[this] {
			Parent->HitStates = EHitStateType::Normal;
		}, 1.f, false);
}

void ULedgeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ULedgeComponent, Parent);
}



