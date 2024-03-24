// copyright MGK


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MyPlayerController.h"
#include "Player/MyPlayerState.h"
#include "UI/HUD/MyHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController); //Server-Only

	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetCharacterLevel()
{
	AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
	check(PS);
	return PS->GetCharacterLevel();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState);

	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(MyPlayerState, this);
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
	if (PlayerController)
	{
		AMyHUD* MyHUD = Cast<AMyHUD>(PlayerController->GetHUD());
		MyHUD->InitOverlay(PlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
	}

	InitializeDefaultAttributes();
}
