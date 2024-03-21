// copyright MGK


#include "AbilitySystem/MyAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UMyAttributeSet::UMyAttributeSet()
{
	InitHealth(40);
	InitMaxHealth(100);
	InitMana(100);
	InitMaxMana(200);
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
	}
}

void UMyAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& Props) const
{
	//Source = causer, Target = target(owner of THIS attribute set)
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.Source.ASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.Source.ASC) && Props.Source.ASC->AbilityActorInfo.IsValid() && Props.Source.ASC->AbilityActorInfo->AvatarActor.
		IsValid())
	{
		Props.Source.AvatarActor = Props.Source.ASC->AbilityActorInfo->AvatarActor.Get();
		Props.Source.Controller = Props.Source.ASC->AbilityActorInfo->PlayerController.Get();
		if (!Props.Source.Controller && Props.Source.AvatarActor)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.Source.AvatarActor))
			{
				Props.Source.Controller = Pawn->GetController();
			}
		}
		if (Props.Source.Controller)
		{
			Props.Source.Character = Cast<ACharacter>(Props.Source.Controller->GetPawn());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.Target.AvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.Target.Controller = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.Target.Character = Cast<ACharacter>(Props.Target.AvatarActor);
		Props.Target.ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			Props.Target.AvatarActor);
	}
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldHealth);
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxHealth, OldMaxHealth);
}

void UMyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Mana, OldMana);
}

void UMyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxMana, OldMaxMana);
}

