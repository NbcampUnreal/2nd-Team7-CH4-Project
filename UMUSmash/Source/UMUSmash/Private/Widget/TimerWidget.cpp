


#include "Widget/TimerWidget.h"

#include "Components/TextBlock.h"
#include "Managers/UMUGameState.h"


void UTimerWidget::UpdateCountdownWidget()
{
	auto* GameState = GetWorld()->GetGameState<AUMUGameState>();
	if (GameState)
	{
		if (GameState->GetInGameMode() == EInGameModes::Time)
		{
			const double RemainingSeconds = GameState->GetInterpolatedTime(); 
			Minutes = RemainingSeconds/60;
			Seconds = RemainingSeconds - double(Minutes * 60);

			if (Seconds >= 10)
			{
				NewCount = FText::FromString(FString::Printf(TEXT("Time\n%d:%f"), Minutes, Seconds));	
			}
			else
			{
				NewCount = FText::FromString(FString::Printf(TEXT("Time\n%d:0%f"), Minutes, Seconds));
			}
			CountdownText->SetText(NewCount);	
		}
	}
}

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ensure(CountdownText);
}

void UTimerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	UpdateCountdownWidget();
}
