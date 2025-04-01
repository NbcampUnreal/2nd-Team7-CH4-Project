


#include "AI\DefaultAI.h"

// Sets default values
ADefaultAI::ADefaultAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

