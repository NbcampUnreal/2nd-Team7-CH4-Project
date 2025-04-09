

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UMUItemInterface.h"
#include "DefaultItem.generated.h"



class UBoxComponent;

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
	UBoxComponent* Collision;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Property")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Property")
	FName ItemName;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	float GravityStrength;
	UPROPERTY(EditAnywhere, Category = "Gravity")
	float FallingSpeed;
	UPROPERTY(EditAnywhere, Category = "Gravity")
	bool UseCustomGravity;

	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;


	// Called when the game starts or when spawned

	virtual void DestroyItem();

	virtual void BeginPlay();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime);

	
	FName GetItemType() const;


	FName GetItemName() const;


private:

	void Gravity(float DeltaTime);
};
