// copyright MGK


#include "MyAssetManager.h"

#include "MyGameplayTags.h"

const UMyAssetManager& UMyAssetManager::Get()
{
	check(GEngine);
	UMyAssetManager* AuraAssetManager = Cast<UMyAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMyGameplayTags::InitializeNativeGameplayTags();
}
