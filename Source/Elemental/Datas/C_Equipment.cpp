#include "C_Equipment.h"
#include "GameFramework/Character.h"
#include "../Components/C_StateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AC_Equipment::AC_Equipment()
{

}

void AC_Equipment::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = Cast<UC_StateComponent>(OwnerCharacter->GetComponentByClass(UC_StateComponent::StaticClass()));
}

void AC_Equipment::Equip_Implementation()
{
	State->SetEquipState();

	if(!!EquipmentData.AnimMontage)
		OwnerCharacter->PlayAnimMontage(EquipmentData.AnimMontage, EquipmentData.PlayRate, EquipmentData.StartSection);
	else
	{
		Begin_Equip();
		End_Equip();
	}

	if (EquipmentData.bPawnControl == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	}

}

void AC_Equipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
}

void AC_Equipment::End_Equip_Implementation()
{
	State->SetIdleState();
}

void AC_Equipment::Unequip_Implementation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (OnUnequipmentDelegate.IsBound())
		OnUnequipmentDelegate.Broadcast();
}

