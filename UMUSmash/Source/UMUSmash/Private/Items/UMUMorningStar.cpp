
#include "Items/UMUMorningStar.h"
#include "Character/BaseCharacter.h"



AUMUMorningStar::AUMUMorningStar()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/PlatformFighterKit/Item/Morning_Star/morning_star.morning_star"));
	if (StaticMeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	}


}

void AUMUMorningStar::BeginPlay()
{
	Super::BeginPlay();

}

void AUMUMorningStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AUMUMorningStar::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(Activator);
	if (TargetCharacter)
	{
		if (!TargetCharacter->FindComponentByClass<UUMUMeleeItemComponent>())
		{

			USkeletalMeshComponent* CharacterSkelMesh = TargetCharacter->GetMesh();

			if (CharacterSkelMesh)
			{
				UStaticMeshComponent* StaticMeshComp = NewObject<UStaticMeshComponent>(TargetCharacter);

				if (StaticMeshComp)
				{
					StaticMeshComp->SetStaticMesh(StaticMesh->GetStaticMesh());
					StaticMeshComp->RegisterComponent();
					TargetCharacter->AddOwnedComponent(StaticMeshComp);
					
					StaticMeshComp->AttachToComponent(
						CharacterSkelMesh,
						FAttachmentTransformRules::SnapToTargetNotIncludingScale,
						TEXT("hand_rSocket"));

				}
			}
			
			WeaponComponent = NewObject<UUMUMeleeItemComponent>(TargetCharacter);
			if (WeaponComponent)
			{
				
				WeaponComponent->RegisterComponent();
				TargetCharacter->AddOwnedComponent(WeaponComponent);
			}
		}
	}


	DestroyItem();
}
