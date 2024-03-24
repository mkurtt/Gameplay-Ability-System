// copyright MGK


#include "AbilitySystem/Data/AttributeInfo.h"

FMyAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	if (AttributeInformation.Contains(AttributeTag))
	{
		return AttributeInformation[AttributeTag];
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this))
	}
	
	return FMyAttributeInfo();
}
