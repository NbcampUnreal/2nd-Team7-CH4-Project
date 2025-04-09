


#include "Character/FootStepComp.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFootStepComp::UFootStepComp()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UFootStepComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}




//void UFootStepComp::ProcessDetectFeet(float AxisValue)
//{
//	Volume = FMath::Clamp(FMath::Abs(AxisValue), 0.0f, 1.0f);
//
//	static bool bCanTrigger = true;
//
//	if (bCanTrigger)
//	{
//		FootLocation = GetOwner()->GetActorLocation();
//
//		SurfaceType = SurfaceType_Default;
//
//
//		TriggerFootStep();
//
//
//		bCanTrigger = false;
//	}
//	else
//	{
//
//	}
//}

void UFootStepComp::TriggerFootStep()
{
	if (FootPrintSounds.Num() > 0 && FootPrintSounds[0])
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootPrintSounds[0], FootLocation, Volume);
	}

	UParticleSystem* SelectedParticle = nullptr;

	switch (CurrentPlayerState)
	{
	case EPlayerStateType::Idle:				SelectedParticle = IdleParticle; break;
	case EPlayerStateType::walkrun:				SelectedParticle = WalkRunParticle; break;
	case EPlayerStateType::sprint:				SelectedParticle = SprintParticle; break;
	case EPlayerStateType::jump:				SelectedParticle = JumpParticle; break;
	case EPlayerStateType::fall:				SelectedParticle = FallParticle; break;
	case EPlayerStateType::hit:					SelectedParticle = HitParticle; break;
	case EPlayerStateType::launch:				SelectedParticle = LaunchParticle; break;
	case EPlayerStateType::crouch:				SelectedParticle = CrouchParticle; break;
	case EPlayerStateType::ledge:				SelectedParticle = LedgeParticle; break;
	case EPlayerStateType::dead:				SelectedParticle = DeadParticle; break;
	case EPlayerStateType::shiled:				SelectedParticle = ShieldParticle; break;
	case EPlayerStateType::tumble:				SelectedParticle = TumbleParticle; break;
	case EPlayerStateType::shildtumble:			SelectedParticle = ShieldTumbleParticle; break;
	case EPlayerStateType::prone:				SelectedParticle = ProneParticle; break;
	case EPlayerStateType::stun:				SelectedParticle = StunParticle; break;
	case EPlayerStateType::dizzy:				SelectedParticle = DizzyParticle; break;
	case EPlayerStateType::ability:				SelectedParticle = AbilityParticle; break;
	case EPlayerStateType::Dodge:				SelectedParticle = DodgeParticle; break;
	case EPlayerStateType::FreeFall:			SelectedParticle = FreeFallParticle; break;
	case EPlayerStateType::Held:				SelectedParticle = HeldParticle; break;
	case EPlayerStateType::Hold:				SelectedParticle = HoldParticle; break;
	default:									SelectedParticle = DefaultParticle; break;
	}
	if (SelectedParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedParticle, FootLocation);
	}
}

// UMUTypes enum°ª