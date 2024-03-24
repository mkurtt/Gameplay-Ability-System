// copyright MGK


#include "AbilitySystem/Abilities/MyProjectileSpell.h"

#include "Actor/MyProjectile.h"
#include "Interaction/CombatInterface.h"

void UMyProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		//TODO: Set projectile rotation
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		
		AMyProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMyProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projectile a GameplayEffectSpec 
		
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
