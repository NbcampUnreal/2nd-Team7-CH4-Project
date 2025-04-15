


#include "Items/UMUHammer.h"


AUMUHammer::AUMUHammer()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/PlatformFighterKit/Item/Hammer/Hammer.Hammer"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	}

}


void AUMUHammer::BeginPlay()
{
}

void AUMUHammer::Tick(float DeltaTime)
{
}



void AUMUHammer::ActivateItem(AActor* Activator)
{
}
