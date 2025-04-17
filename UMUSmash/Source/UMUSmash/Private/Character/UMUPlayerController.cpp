#include "Character/UMUPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

AUMUPlayerController::AUMUPlayerController()
{
	BGMComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMComponent"));
}

void AUMUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("In BeginPlay"));

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	if (!BGMComponent)
	{
		BGMComponent = NewObject<UAudioComponent>(this);
		if (BGMComponent)
		{
			BGMComponent->bAutoActivate = false;
			BGMComponent->bIsUISound = false;
			BGMComponent->bAllowSpatialization = false;
			BGMComponent->RegisterComponentWithWorld(GetWorld());
		}
	}
}

void AUMUPlayerController::PlayBGM(USoundBase* NewBGM)
{
	UE_LOG(LogTemp, Error, TEXT("PlayBGM called"));
	UE_LOG(LogTemp, Warning, TEXT("PlayBGM called"));
	UE_LOG(LogTemp, Warning, TEXT("PlayBGM called"));
	if (BGMComponent && NewBGM)
	{
		if (BGMComponent->IsPlaying())
		{
			BGMComponent->Stop();
		}
		BGMComponent->SetSound(NewBGM);
		BGMComponent->Play();
	}
}

void AUMUPlayerController::StopBGM()
{
	if (BGMComponent && BGMComponent->IsPlaying())
	{
		BGMComponent->Stop();
	}
}