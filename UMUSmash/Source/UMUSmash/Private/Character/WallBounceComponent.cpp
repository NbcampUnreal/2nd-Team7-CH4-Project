


#include "Character/WallBounceComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Character\BaseCharacter.h"
#include "Character\CharStatComponent.h"
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
	CharacterMovement = Parent->GetCharacterMovement();
	// ...
	
}

void UWallBounceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(DelayTimer);
	GetWorld()->GetTimerManager().ClearTimer(WallBounceDelayTimer);
}

void UWallBounceComponent::WallBouceCalc()
{
	CharacterMovement->GravityScale = Parent->CharStatComponent->DefaultGravityScale;
	FVector BounceVectorCalc = Parent->BounceVector;
	BounceVectorCalc.X = 0.f;
	if (Parent->InputDirection == EInputDirection::Up || Parent->InputDirection == EInputDirection::Down)
	{
		BounceVectorCalc.Z *= -1;
	}
	else if (Parent->InputDirection == EInputDirection::Up || Parent->InputDirection == EInputDirection::Down)
	{
		BounceVectorCalc.Y *= -1;
	}
	Parent->LaunchCharacter(BounceVectorCalc, true, true);

	GetWorld()->GetTimerManager().SetTimer(DelayTimer,
		[this]
		{
			Parent->Bounce = false;
		},
		0.1f,
		false);
}

void UWallBounceComponent::WallBounce()
{
	Parent->SetActorRotation(FRotator(0, 0, 90), ETeleportType::TeleportPhysics);
	Parent->Bounce = true;
	Parent->WallDetection = false;
	CharacterMovement->GravityScale = 0.f;
	Parent->LaunchCharacter(FVector(0, 1, 1), true, true);
	CharacterMovement->StopActiveMovement();
	CharacterMovement->GravityScale = 0.f;
	GetWorld()->GetTimerManager().SetTimer(WallBounceDelayTimer,
		this,
		&UWallBounceComponent::WallBouceCalc,
		0.2f,
		false);
}
