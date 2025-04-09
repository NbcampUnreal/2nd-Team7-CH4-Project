


#include "Items/UMUItemManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

void UUMUItemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUMUItemManager::Deinitialize()
{
	Super::Deinitialize();

}

void UUMUItemManager::AddSpawnerArray(AUMUItemSpawner* Spawner)
{
	SpawnerArray.Add(Spawner);
	UE_LOG(LogTemp, Warning, TEXT("ItemManager ItemArray Add - Name : %s"), *Spawner->GetName());
}

void UUMUItemManager::SelectSpawner()
{
	if (!SpawnerArray.IsEmpty())
	{
		int32 RandomIndex = FMath::RandRange(0, SpawnerArray.Num() - 1);
	
		//SpawnerArray[RandomIndex]->SpawnItem();
	}
}

FUMUItemSpawnRow UUMUItemManager::SelectItem()
{

	return FUMUItemSpawnRow();
}

