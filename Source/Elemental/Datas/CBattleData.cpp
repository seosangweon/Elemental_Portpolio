#include "CBattleData.h"
#include "C_Equipment.h"
#include "CWeapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "../Weapons/C_Weapon_Sword.h"
#include "C_Action.h"
#include "C_AOSkill.h"

void UCBattleData::BeginPlay(class ACharacter* OwnerCharacter)
{
	//FTransform transform  = OwnerCharacter->GetActorTransform();
	FTransform transform;
	if (!!WeaponClass)
	{
		//Spawn WeaponClass
		Weapon = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACWeapon>(WeaponClass, transform, OwnerCharacter);
		UGameplayStatics::FinishSpawningActor(Weapon, transform);
	}
	
	if (!!EquipmentClass)  
	{
		//Spawn EquipmentClass
		Equipment = OwnerCharacter->GetWorld()->SpawnActorDeferred<AC_Equipment>(EquipmentClass, transform, OwnerCharacter);
		Equipment->AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative,true));
		Equipment->SetData(EquipmentData);
		UGameplayStatics::FinishSpawningActor(Equipment,transform);

		if (!!Weapon)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Weapon, &ACWeapon::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Weapon, &ACWeapon::OnUnequip);
		}
	}

	//if (!!ActionClass && SkillClass)
	//{
	if (!!ActionClass)
	{//Spawn ActionClass
		Action = OwnerCharacter->GetWorld()->SpawnActorDeferred<AC_Action>(ActionClass, transform, OwnerCharacter);
		Action->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Action->SetDatas(ActionDatas);
		UGameplayStatics::FinishSpawningActor(Action, transform);
		if (!!SkillClass)
		{
			Skill = OwnerCharacter->GetWorld()->SpawnActorDeferred<AC_Action>(SkillClass, transform, OwnerCharacter);
			Skill->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
			Skill->SetSkillDatas(SkillDatas);
			UGameplayStatics::FinishSpawningActor(Skill, transform);
		}
		
		if (!!Weapon)
		{
			Weapon->OnWeaponBeginOverlap.AddDynamic(Action, &AC_Action::OnWeaponBeginOverlap);
			Weapon->OnWeaponEndOverlap.AddDynamic(Action, &AC_Action::OnWeaponEndOverlap);
		}
	}
	if (!!AOEClass)
	{
		AOE = OwnerCharacter->GetWorld()->SpawnActorDeferred<AC_AOSkill>(AOEClass, transform, OwnerCharacter);
		AOE->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		UGameplayStatics::FinishSpawningActor(AOE, transform);
	}

}