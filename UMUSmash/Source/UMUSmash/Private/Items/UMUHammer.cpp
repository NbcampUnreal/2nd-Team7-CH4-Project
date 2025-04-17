
#include "Items/UMUHammer.h"
#include "Character/BaseCharacter.h"



AUMUHammer::AUMUHammer()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/PlatformFighterKit/Item/Hammer/Hammer.Hammer"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	}
	ItemType = EItemType::Hammer;
}


void AUMUHammer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUMUHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AUMUHammer::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	DeActivation();
}
