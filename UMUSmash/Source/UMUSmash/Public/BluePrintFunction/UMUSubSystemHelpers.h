

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UMUSmash/Public/Items/UMUItemManager.h"
#include "UMUSubSystemHelpers.generated.h"

/**
 * 
 */
UCLASS()
class UMUSMASH_API UUMUSubSystemHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Subsystem")
	static UUMUItemManager* GetItemManager(UObject* WorldContextObject);
};
