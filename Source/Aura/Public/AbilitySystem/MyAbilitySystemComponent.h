// copyright MGK

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*Asset Tags*/);

/**
 * 
 */
UCLASS()
class AURA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	 void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	
protected:
	void EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
