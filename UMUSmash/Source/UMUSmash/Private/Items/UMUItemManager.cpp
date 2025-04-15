#include "Items/UMUItemManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

UUMUItemManager::UUMUItemManager()
{
	ConstructorHelpers::FObjectFinder<UDataTable> ItemDataObject(TEXT("/Game/PlatformFighterKit/Item/ItemData/ItemClassTable.ItemClassTable"));
	if (ItemDataObject.Succeeded()) //ItemDataReadFaild
	{
		ItemClassDataTable = ItemDataObject.Object;
	}
}

void UUMUItemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RoadItemData();


}

void UUMUItemManager::Deinitialize()
{
	Super::Deinitialize();

}

void UUMUItemManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

}

void UUMUItemManager::AddSpawnerArray(AUMUItemSpawner* Spawner)
{
	SpawnerArray.Add(Spawner);
	UE_LOG(LogTemp, Warning, TEXT("ItemManager ItemArray Add - Name : %s"), *Spawner->GetName());
}

void UUMUItemManager::SelectSpawnerRun()
{
	if (!SpawnerArray.IsEmpty())
	{
		int32 RandomIndex = FMath::RandRange(0, SpawnerArray.Num() - 1);
		SpawnerArray[RandomIndex]->SpawnItem(SelectItem().ItemClass.Get());
	}
}

FUMUItemSpawnRow UUMUItemManager::SelectItem()
{
	check(!ItemArray.IsEmpty());

	int32 RandomIndex = FMath::RandRange(0, ItemArray.Num() - 1);
	return ItemArray[RandomIndex];


}

void UUMUItemManager::RoadItemData()
{
	check(ItemClassDataTable != nullptr);
	TArray<FUMUItemSpawnRow*> OutRows;
	ItemClassDataTable->GetAllRows<FUMUItemSpawnRow>(TEXT("MyItemLoad"), OutRows);
	for (FUMUItemSpawnRow* Row : OutRows)
	{
		if (Row)
		{
			ItemArray.Add(*Row);
		}
	}
}
