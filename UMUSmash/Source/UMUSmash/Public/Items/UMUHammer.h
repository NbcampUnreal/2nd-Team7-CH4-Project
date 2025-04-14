

#pragma once

#include "CoreMinimal.h"
#include "Items/DefaultItem.h"
#include "Items/Components/UMUMeleeItemComponent.h"
#include "UMUHammer.generated.h"

/**
 * 
 */
UCLASS()
class UMUSMASH_API AUMUHammer : public ADefaultItem
{
	GENERATED_BODY()
	


protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	AUMUHammer();

	virtual void ActivateItem(AActor* Activator) override;

private:
	UPROPERTY()
	UUMUMeleeItemComponent* WeaponComponent;

};
