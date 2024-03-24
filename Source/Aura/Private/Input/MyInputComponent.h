// copyright MGK

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/MyInputConfig.h"
#include "MyInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UMyInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UMyInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UMyInputComponent::BindAbilityActions(const UMyInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (auto& Action : InputConfig->AbilityInputActions)
	{
		if (Action.Value && Action.Key.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Started, Object, PressedFunc, Action.Key);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Completed, Object, ReleasedFunc, Action.Key);
			}
			if (HeldFunc)
			{
				BindAction(Action.Value, ETriggerEvent::Triggered, Object, HeldFunc, Action.Key);
			}
		}
	} 
}
