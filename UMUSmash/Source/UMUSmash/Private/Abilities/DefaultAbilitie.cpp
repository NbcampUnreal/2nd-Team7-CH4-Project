


#include "Abilities\DefaultAbilitie.h"

// Sets default values
ADefaultAbilitie::ADefaultAbilitie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultAbilitie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultAbilitie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

