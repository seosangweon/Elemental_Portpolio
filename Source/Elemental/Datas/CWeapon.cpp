#include "CWeapon.h"
#include "../Components/C_StateComponent.h"
#include "../Components/C_BattleComponent.h"
#include "Gameframework/Character.h"
#include "Components/CapsuleComponent.h"

ACWeapon::ACWeapon()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(Scene);
}

void ACWeapon::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = Cast<UC_StateComponent>(OwnerCharacter->GetComponentByClass(UC_StateComponent::StaticClass()));
	Battle = Cast<UC_BattleComponent>(OwnerCharacter->GetComponentByClass(UC_BattleComponent::StaticClass()));

	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* shape : ShapeComponents)
	{
		shape->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon::OnComponentBeginOverlap);
		shape->OnComponentEndOverlap.AddDynamic(this, &ACWeapon::OnComponentEndOverlap);
	}

	OffCollision();

	Super::BeginPlay();
}

void ACWeapon::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == OwnerCharacter) return;
	if (OtherActor->GetClass() == OwnerCharacter->GetClass()) return;

	if (OnWeaponBeginOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
		if (otherCharacter == nullptr) return;

		OnWeaponBeginOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void ACWeapon::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnWeaponEndOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
		if (otherCharacter == nullptr) return;

		OnWeaponEndOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}


void ACWeapon::OnCollision()
{
	for (UShapeComponent* shape : ShapeComponents)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACWeapon::OffCollision()
{
	for (UShapeComponent* shape : ShapeComponents)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACWeapon::AttachSocket(FName InName)
{
	AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative,true), InName);
	
}


