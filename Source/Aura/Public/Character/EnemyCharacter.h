// copyright MGK

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public AMyCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void BeginPlay() override;

#pragma region EnemyInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
#pragma endregion
};