

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UMUItemInterface.h"
#include "DefaultItem.generated.h"



class USphereComponent;

UCLASS()
class UMUSMASH_API ADefaultItem : public AActor, public IUMUItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultItem();

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Compoenet")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Compoenet")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Compoenet")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Compoenet")
	FName ItemType;

	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;

	virtual FName GetItemType() const override;

	// Called when the game starts or when spawned
	virtual void BeginPlay();

	virtual void DestroyItem();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime);

};
