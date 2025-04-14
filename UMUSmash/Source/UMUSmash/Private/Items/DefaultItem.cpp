


#include "Items\DefaultItem.h"
#include"Components/BoxComponent.h"

// Sets default values
ADefaultItem::ADefaultItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	/*Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);*/
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	//SKeletalMesh->SetupAttachment(Scene);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(StaticMesh);
	/*Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));*/
	

	/*SKeletalMesh->SetSimulatePhysics(false);
	SKeletalMesh->SetEnableGravity(false);
	UseCustomGravity = true;
	GravityStrength = -980.0f;
	FallingSpeed = 30.0f;*/

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
		ActivateItem(OtherActor);
	}
}

void ADefaultItem::ActivateItem(AActor* Activator)
{
}





// Called when the game starts or when spawned
void ADefaultItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ADefaultItem::DestroyItem()
{
	Destroy();
}

// Called every frame


