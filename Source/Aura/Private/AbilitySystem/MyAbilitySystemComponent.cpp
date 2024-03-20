// copyright MGK


#include "AbilitySystem/MyAbilitySystemComponent.h"

void UMyAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::EffectApplied);
}

void UMyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                              FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer Tags;
	EffectSpec.GetAllAssetTags(Tags);
	for (const FGameplayTag& Tag : Tags)
	{
		//TODO: Broadcast the tag to the widget controller
	}
}
