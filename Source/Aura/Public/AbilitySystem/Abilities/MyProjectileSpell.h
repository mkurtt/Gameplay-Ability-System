// copyright MGK

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MyGameplayAbility.h"
#include "MyProjectileSpell.generated.h"

class AMyProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UMyProjectileSpell : public UMyGameplayAbility
{
	GENERATED_BODY()


protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMyProjectile> ProjectileClass;
};
