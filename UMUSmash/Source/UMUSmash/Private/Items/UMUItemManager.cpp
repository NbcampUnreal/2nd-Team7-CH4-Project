


#include "Items/UMUItemManager.h"
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
	SpawnerArray.Add(Spawner->GetClass());
	UE_LOG(LogTemp, Warning, TEXT("ItemManager ItemArray Add - Name : %s"), *Spawner->GetName());
}
