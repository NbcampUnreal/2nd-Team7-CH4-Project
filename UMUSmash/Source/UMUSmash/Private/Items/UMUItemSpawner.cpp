


#include "Items/UMUItemSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Items/UMUItemManager.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AUMUItemSpawner::AUMUItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComponent->SetupAttachment(Scene);
	NiagaraComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	NiagaraComponent->bAutoActivate = false;

	ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraEffectObject(TEXT("/Game/PlatformFighterKit/Item/VFX/KTP_Effect/Particles/Fly/Others/energy_06_01.energy_06_01"));
	if (NiagaraEffectObject.Succeeded())
	{
		NiagaraEffect = NiagaraEffectObject.Object;
		NiagaraComponent->SetAsset(NiagaraEffect);
	}

}

// Called when the game starts or when spawned
void AUMUItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	UUMUItemManager* ItemManager = GetWorld()->GetSubsystem<UUMUItemManager>();
	check(ItemManager);

	ItemManager->AddSpawnerArray(this);
	
}

void AUMUItemSpawner::SpawnItem(TSubclassOf<AActor> SpawnActor)
{
	if (NiagaraEffect)
	{
		NiagaraComponent->Activate();
	}

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("CreateItem"), SpawnActor);
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.3f, false);
		
}

void AUMUItemSpawner::CreateItem(TSubclassOf<AActor> Item)
{
	FVector Location = this->GetActorLocation();
	FRotator RandomRot = UKismetMathLibrary::RandomRotator(true);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	GetWorld()->SpawnActor<AActor>(Item, Location, RandomRot, SpawnParams);

}

// Called every frame
void AUMUItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

