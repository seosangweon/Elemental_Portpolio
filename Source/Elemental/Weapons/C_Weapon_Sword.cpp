#include "C_Weapon_Sword.h"
#include "Components/SkeletalMeshComponent.h"

AC_Weapon_Sword::AC_Weapon_Sword()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(Scene);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>swordMesh(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));
	if (swordMesh.Succeeded())
		MeshComp->SetSkeletalMesh(swordMesh.Object);

}

void AC_Weapon_Sword::BeginPlay()
{
	Super::BeginPlay();

	AttachSocket("Sword_Socket");
	MeshComp->SetVisibility(true);
	
}

void AC_Weapon_Sword::AttachSocket(FName InName)
{
	Super::AttachSocket(InName);
}

void AC_Weapon_Sword::SetSwordVisible()
{
	MeshComp->SetVisibility(true);
}



