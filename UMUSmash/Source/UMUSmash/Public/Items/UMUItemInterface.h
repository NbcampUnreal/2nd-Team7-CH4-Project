

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UMUItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUMUItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UMUSMASH_API IUMUItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) = 0;

	UFUNCTION()
	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) = 0;

	UFUNCTION()
	virtual void ActivateItem(AActor* Activator) = 0;



};
