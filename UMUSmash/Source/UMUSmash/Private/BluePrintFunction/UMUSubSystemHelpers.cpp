


#include "BluePrintFunction/UMUSubSystemHelpers.h"

UUMUItemManager* UUMUSubSystemHelpers::GetItemManager(UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return nullptr;

    return World->GetSubsystem<UUMUItemManager>();
}
