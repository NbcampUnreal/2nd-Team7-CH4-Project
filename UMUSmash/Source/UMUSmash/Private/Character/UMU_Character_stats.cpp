

#include "Kismet/GameplayStatics.h"
#include "Character/UMU_Character_stats.h"

// Sets default values for this component's properties
UUMU_Character_stats::UUMU_Character_stats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUMU_Character_stats::BeginPlay()
{
	Super::BeginPlay();

	Parent = Cast<ABaseCharacter>(GetOwner());

	if (!Parent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMU_Character_Stats: Parent casting fail"));
	}
	// ...
	
	//take damege는 nomal일때 ==을 받음
}


// Called every frame
void UUMU_Character_stats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUMU_Character_stats::ScreenShake(float RumbleInten, float RumbleDuration)
{
	if (!Parent)
	{
		return;
	}



}