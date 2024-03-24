// copyright MGK


#include "Character/MyCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacterBase::InitAbilityActorInfo()
{
}

void AMyCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AMyCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes);
	ApplyEffectToSelf(DefaultSecondaryAttributes);
	ApplyEffectToSelf(DefaultVitalAttributes);
}

void AMyCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	UMyAbilitySystemComponent* ASC = CastChecked<UMyAbilitySystemComponent>(AbilitySystemComponent);

	ASC->AddCharacterAbilities(StartupAbilities);
}
