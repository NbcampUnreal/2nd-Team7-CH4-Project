#pragma once

#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UMUPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class UMUSMASH_API AUMUPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUMUPlayerController();
	
	virtual void BeginPlay() override;
	//BGM component
	UFUNCTION(BlueprintCallable)
	void PlayBGM(USoundBase* NewBGM);

	UFUNCTION(BlueprintCallable)
	void StopBGM();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY()
	UAudioComponent* BGMComponent;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> VerticalInputAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> HorizontalInputAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> SmashAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ShieldAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> DodgeAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ItemPickUpAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ItemUseAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> ItemThrowAction;

};
