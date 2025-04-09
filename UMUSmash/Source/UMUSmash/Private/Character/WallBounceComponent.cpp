


#include "Character/WallBounceComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Character\BaseCharacter.h"
// Sets default values for this component's properties
UWallBounceComponent::UWallBounceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWallBounceComponent::BeginPlay()
{
	Super::BeginPlay();
	Parent = Cast<ABaseCharacter>(GetOwner());
	// ...
	
}

void UWallBounceComponent::WallBounce()
{
	Parent->SetActorRotation(FRotator(0, 0, 90), ETeleportType::TeleportPhysics);

}
