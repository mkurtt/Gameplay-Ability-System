// copyright MGK


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMyAttributeSet* AS = CastChecked<UMyAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	OnManaChanged.Broadcast(AS->GetMana());
	OnMaxManaChanged.Broadcast(AS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMyAttributeSet* AS = CastChecked<UMyAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data){OnManaChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data){OnMaxManaChanged.Broadcast(Data.NewValue);});

	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag("Message")))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRow.Broadcast(*Row);
				}
			}
		}
	);
}