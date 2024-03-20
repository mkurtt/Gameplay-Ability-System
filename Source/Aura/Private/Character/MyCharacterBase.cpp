// copyright MGK


#include "Character/MyCharacterBase.h"

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
