// copyright MGK


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UMyAttributeSet* AS = CastChecked<UMyAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BoardcastAttributeInfo(Pair.Key,Pair.Value);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	const UMyAttributeSet* AS = CastChecked<UMyAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	for (auto Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
		{
				BoardcastAttributeInfo(Pair.Key,Pair.Value);
		});
	}
}

void UAttributeMenuWidgetController::BoardcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FMyAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.Value = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
