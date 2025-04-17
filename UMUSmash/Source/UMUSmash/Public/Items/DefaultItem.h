

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UMUItemInterface.h"
#include "UMUTypes.h"
#include "DefaultItem.generated.h"



class UBoxComponent;

UCLASS()
class UMUSMASH_API ADefaultItem : public AActor, public IUMUItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultItem();

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyItem();

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Compoenet")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Compoenet")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Compoenet")
	UBoxComponent* Collision;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Property")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Property")
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Property")
	bool Activate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FVector DesiredScale;

	

	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void ActivateItem(AActor* Activator) override;
	

	// Called when the game starts or when spawned
	UFUNCTION()
	void DeActivation();

	// Called every frame
	virtual void Tick(float DeltaTime);

	virtual void BeginPlay();

	virtual void OnConstruction(const FTransform& Transform) override;



private:
	UPROPERTY()
	bool FloorHit = false;
};
