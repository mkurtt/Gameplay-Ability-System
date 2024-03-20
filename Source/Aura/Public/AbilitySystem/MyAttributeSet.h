// copyright MGK

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectObject
{
	GENERATED_BODY()

	FEffectObject() {}
	FEffectObject(UAbilitySystemComponent* ASC, AActor* AA, AController* Controller, ACharacter* Char)
	: ASC(ASC), AvatarActor(AA), Controller(Controller), Character(Char) {}
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> AvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> Controller = nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> Character = nullptr;
	
};

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}
	
	FEffectObject Source;
	FEffectObject Target;
	FGameplayEffectContextHandle EffectContextHandle;
};


/**
 * 
 */
UCLASS()
class AURA_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMyAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// -- Health --
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	ATTRIBUTE_ACCESSORS(ThisClass, Health);

	// -- MaxHealth --
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);

	// -- Mana --
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);

	// -- MaxMana --
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

};
