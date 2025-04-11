

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

class UTextBlock;

UCLASS()
class UMUSMASH_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateCountdownWidget();
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
	

	
protected:
	UPROPERTY(meta=(BindWidget="Widget"))
	TObjectPtr<UTextBlock> CountdownText;

	int32 Minutes = 0;
	double Seconds = 0;
	FText NewCount;
	
};
