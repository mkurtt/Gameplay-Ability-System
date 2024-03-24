// copyright MGK


#include "AbilitySystem/MyAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerState.h"
#include "UI/HUD/MyHUD.h"
#include "UI/WidgetController/MyWidgetController.h"

UOverlayWidgetController* UMyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMyHUD* HUD = Cast<AMyHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UMyAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMyHUD* HUD = Cast<AMyHUD>(PC->GetHUD()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
