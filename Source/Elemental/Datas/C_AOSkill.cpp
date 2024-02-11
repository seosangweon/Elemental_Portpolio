#include "C_AOSkill.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"

AC_AOSkill::AC_AOSkill()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(Scene);

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Scene);

	Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
	Decal->SetupAttachment(Box);
	
	Decal->SetVisibility(false);

	
}

void AC_AOSkill::BeginPlay()
{
	Super::BeginPlay();
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AC_AOSkill::OnComponentBeginOverlap);

}
void AC_AOSkill::OnCollision()
{
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AC_AOSkill::OffCollision()
{
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AC_AOSkill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;


	if (OnSkillBeginOverlap.IsBound())
		OnSkillBeginOverlap.Broadcast(SweepResult);

}


