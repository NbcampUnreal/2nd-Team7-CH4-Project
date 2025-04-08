
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UMU_FX_component.h"

// Sets default values for this component's properties
UUMU_FX_component::UUMU_FX_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUMU_FX_component::BeginPlay()
{
	Super::BeginPlay();
	Parent = Cast<ABaseCharacter>(GetOwner());

	if (!Parent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMU_FX_component: Parent casting fail"));
	}
	Do_Once = false;
	const ConstructorHelpers::FObjectFinder<UParticleSystem> SmokeTrailAsset(TEXT("/Game/PlatformFighterKit/Assets/FX/Particles/Common/P_SmokeTrail.P_SmokeTrail"));
	if (SmokeTrailAsset.Succeeded())
	{
		P_SmokeTrail = SmokeTrailAsset.Object;
	}
}

void UUMU_FX_component::Fx_Main_Roop()
{
	if (!Parent)
	{
		return;
	}
	//plyaerstates의 launch와 tumble을 사용하기
	if (Parent->PlayerStateType == EPlayerStateType::launch || Parent->PlayerStateType == EPlayerStateType::tumble)
	{
		//do once 는 한번만 실행하는 코드 Reset은 그게 사용되면 다시 실행가능하게하는 코드
		if (!Do_Once)
		{
			Do_Once = true;
			Smoke = UGameplayStatics::SpawnEmitterAttached(
				P_SmokeTrail, // 스모크 경로명 /Game/PlatformFighterKit/Assets/FX/Particles/Common/P_SmokeTrail.P_SmokeTrail
				Parent->GetMesh(),
				FName("pelvis"),
				FVector(0.f, 0.f, 2.f),
				FRotator(0.f, 0.f, 2.f),
				FVector(1.f, 1.f, 1.f),
				EAttachLocation::SnapToTarget,
				true
			);
		}
	}
	else
	{
		if (Smoke && Smoke->IsValidLowLevel())
		{
			Do_Once = false;
			Smoke->EndTrails();
		}
	}
}


