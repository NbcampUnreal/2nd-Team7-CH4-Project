

#pragma once

#include "CoreMinimal.h"
#include "Items/DefaultItem.h"
#include "Items/Components/UMUMeleeItemComponent.h"
#include "UMUMorningStar.generated.h"

/**
 *
 */
UCLASS()
class UMUSMASH_API AUMUMorningStar : public ADefaultItem
{
	GENERATED_BODY()



public:
	AUMUMorningStar();

	virtual void ActivateItem(AActor* Activator) override;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


};
