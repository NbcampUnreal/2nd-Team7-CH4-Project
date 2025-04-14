

#pragma once

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
	void BeginPlay() override;

public:
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> CPUArray = {};
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> MappingContext;
};
