// copyright MGK


#include "Actor/MyEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "Components/SphereComponent.h"

AMyEffectActor::AMyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void AMyEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect!!!!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UMyAttributeSet* MyAttributeSet = Cast<UMyAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UMyAttributeSet::StaticClass()));
		UMyAttributeSet* MutableMyAttributeSet = const_cast<UMyAttributeSet*>(MyAttributeSet);
		MutableMyAttributeSet->SetHealth(MyAttributeSet->GetHealth() + 25);
		MutableMyAttributeSet->SetMana(MyAttributeSet->GetMana() + 25);
		Destroy();
	}
}

void AMyEffectActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	
}

void AMyEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);
}
