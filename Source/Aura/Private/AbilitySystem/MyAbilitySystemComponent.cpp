// copyright MGK


#include "AbilitySystem/MyAbilitySystemComponent.h"

void UMyAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::EffectApplied);
}

void UMyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                              FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);

	EffectAssetTags.Broadcast(AssetTags);
	
	
}
