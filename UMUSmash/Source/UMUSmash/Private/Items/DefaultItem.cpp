


#include "Items\DefaultItem.h"

#include"Components/BoxComponent.h"

// Sets default values
ADefaultItem::ADefaultItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(StaticMesh);


	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADefaultItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ADefaultItem::OnItemEndOverlap);
}

void ADefaultItem::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherComp && OtherComp->ComponentHasTag("Player"))
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
		
	}
}

void ADefaultItem::ActivateItem(AActor* Activator)
{
	if (!Activator)
		return;
	


}




// Called when the game starts or when spawned
void ADefaultItem::BeginPlay()
{
	
	Super::BeginPlay();

	ItemActivation = true;
	
}

void ADefaultItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (UseCustomGravity)
	{
		Gravity(DeltaTime);
	}*/
}

void ADefaultItem::DestroyItem()
{
	this->SetActorHiddenInGame(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

// Called every frame


