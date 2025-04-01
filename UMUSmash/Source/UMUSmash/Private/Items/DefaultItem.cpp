


#include "Items\DefaultItem.h"
#include"Components/SphereComponent.h"

// Sets default values
ADefaultItem::ADefaultItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Scene);
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);


	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADefaultItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ADefaultItem::OnItemEndOverlap);
}

void ADefaultItem::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!")));
		ActivateItem(OtherActor);
	}
}

void ADefaultItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("End Overlap!")));
		ActivateItem(OtherActor);
	}
}

void ADefaultItem::ActivateItem(AActor* Activator)
{
}

FName ADefaultItem::GetItemType() const
{
	return FName();
}

// Called when the game starts or when spawned
void ADefaultItem::BeginPlay()
{
	AActor::BeginPlay();
	
}

void ADefaultItem::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

void ADefaultItem::DestroyItem()
{
	Destroy();
}

// Called every frame


