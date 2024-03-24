// copyright MGK

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MyInputConfig.generated.h"

// USTRUCT(BlueprintType)
// struct FMyInputAction
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditDefaultsOnly)
// 	const class UInputAction* InputAction = nullptr;
//
// 	UPROPERTY(EditDefaultsOnly)
// 	FGameplayTag InputTag = FGameplayTag();
// };

/**
 * 
 */
UCLASS()
class AURA_API UMyInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const class UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound);
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, UInputAction*> AbilityInputActions;
};
