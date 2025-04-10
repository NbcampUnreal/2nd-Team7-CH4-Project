


#include "Items/UMUMorningStar.h"


AUMUMorningStar::AUMUMorningStar()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/PlatformFighterKit/Item/Morning_Star/morning_star.morning_star"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	}


}

void AUMUMorningStar::BeginPlay()
{
	Super::BeginPlay();

}

void AUMUMorningStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AUMUMorningStar::ActivateItem(AActor* Activator)
{

}
