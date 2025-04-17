


#include "Items\DefaultItem.h"
#include "Character/BaseCharacter.h"
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
	DesiredScale = FVector(1.0f, 1.0f, 1.0f);


	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADefaultItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ADefaultItem::OnItemEndOverlap);

	LifeTime = 10.0f;
	Activate = true;
	ItemType = EItemType::None;
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

	ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(Activator);
	if (TargetCharacter)
	{
		if (!TargetCharacter->HasItem)
		{
			TargetCharacter->HasItem = true;


			UStaticMeshComponent* StaticMeshComp = nullptr;

			TArray<UStaticMeshComponent*> MeshComponents;
			TargetCharacter->GetComponents<UStaticMeshComponent>(MeshComponents);

			for (UStaticMeshComponent* Comp : MeshComponents)
			{
				if (Comp && Comp->GetName() == TEXT("ItemMesh"))
				{
					StaticMeshComp = Comp;
					break;
				}
			}

			if (StaticMeshComp)
			{
				StaticMeshComp->SetStaticMesh(StaticMesh->GetStaticMesh());
				StaticMeshComp->SetRelativeScale3D(DesiredScale);
				TargetCharacter->EquipItemType = ItemType;
			}


		}
	}


	DestroyItem();
}





// Called when the game starts or when spawned
void ADefaultItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (StaticMesh)
	{
		StaticMesh->SetRelativeScale3D(DesiredScale);
	}
}

void ADefaultItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Activate)
	{
		LifeTime -= DeltaTime;
	}
	
	if (LifeTime < 0.0f)
	{
		DeActivation();
	}
}

void ADefaultItem::DeActivation()
{
	Activate = false;
	DestroyItem();
}

// Called every frame


