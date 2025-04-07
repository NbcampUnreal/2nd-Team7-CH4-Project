


#include "Character/FootStepComp.h"

// Sets default values for this component's properties
UFootStepComp::UFootStepComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFootStepComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFootStepComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

//void UFootStepComp::TriggerFootStep()
//{
//	if (FootPrintSounds.Num() > 0 && FootPrintSounds[0])
//	{
//		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootPrintSounds[0], FootLocation, Volume);
//	}
//
//	if (FootPrintFX.Num() > 0)
//	{
//		UParticleSystem* Particle = Cast<UParticleSystem>(FootPrintFX[0]);
//		if (Particle)
//		{
//			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, FootLocation);
//		}
//	}
//}