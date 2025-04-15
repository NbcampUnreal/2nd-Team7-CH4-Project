


#include "Items/Components/UMUMeleeItemComponent.h"

// Sets default values for this component's properties
UUMUMeleeItemComponent::UUMUMeleeItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UUMUMeleeItemComponent::BeginAttack()
{
}

void UUMUMeleeItemComponent::EndAttack()
{
}


// Called when the game starts
void UUMUMeleeItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UUMUMeleeItemComponent::CheckHitTargets()
{
}


// Called every frame
void UUMUMeleeItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

