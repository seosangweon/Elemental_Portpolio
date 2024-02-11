#include "C_BattleComponent.h"
#include "Gameframework/Character.h"
#include "../Datas/C_Equipment.h"
#include "../Datas/CWeapon.h"
#include "../Datas/CBattleData.h"
#include "../Datas/C_Action.h"

UC_BattleComponent::UC_BattleComponent()
{

}

void UC_BattleComponent::BeginPlay()
{
	Super::BeginPlay();
	ACharacter* character = Cast<ACharacter>(GetOwner());
	
	for (int32 i = 0; i < (int32)EBattleMode::Max; i++)
	{
		//Spawn Classes(Action,Weapon,Equipment)
		if(!!Datas[i]) 
			Datas[i]->BeginPlay(character);
	}

}

void UC_BattleComponent::SetUnarmedMode()
{
	if(!!Datas[(int32)Type])
		Datas[(int32)Type]->GetEquipment()->Unequip();

	Datas[(int32)EBattleMode::Unarmed]->GetEquipment()->Equip();

	ChangeMode(EBattleMode::Unarmed);
}

void UC_BattleComponent::SetSwordMode()
{
	SetMode(EBattleMode::Sword);
}

void UC_BattleComponent::SetGreatSwordMode()
{
	SetMode(EBattleMode::GreatSword);
}

void UC_BattleComponent::SetMagicMode()
{
	SetMode(EBattleMode::Magic);
}

void UC_BattleComponent::Action()
{
	if (IsUnarmedMode() == true) return;
	if (!!Datas[(int32)Type] && Datas[(int32)Type]->GetAction())
	{
		AC_Action* action = Datas[(int32)Type]->GetAction();
		if(!!action)
			action->Action();
	}
	
}

void UC_BattleComponent::Skill01()
{
	if (IsUnarmedMode() == true) return;
	if (!!Datas[(int32)Type] && Datas[(int32)Type]->GetSkill())
	{
		AC_Action* skill = Datas[(int32)Type]->GetSkill();
		if (!!skill)
			skill->Skill01();
	}
}

void UC_BattleComponent::Skill02()
{
	if (IsUnarmedMode() == true) return;
	if (!!Datas[(int32)Type] && Datas[(int32)Type]->GetSkill())
	{
		AC_Action* skill = Datas[(int32)Type]->GetSkill();
		if (!!skill)
			skill->Skill02();
	}
}

void UC_BattleComponent::OnAim()
{
	if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetAction())
	{
		AC_Action* action = Datas[(int32)Type]->GetAction();

		action->OnAim();
	}
}

void UC_BattleComponent::OffAim()
{
	if (!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetAction())
	{
		AC_Action* action = Datas[(int32)Type]->GetAction();

		action->OffAim();
	}
}

void UC_BattleComponent::Dead()
{
	OffAllCollisions();
}

void UC_BattleComponent::End_Dead()
{
	
}

void UC_BattleComponent::OffAllCollisions()
{
	for (auto data : Datas)
	{
		if (data == nullptr)
			continue;

		if(data->GetWeapon() == nullptr)
			continue;

		data->GetWeapon()->OffCollision();
	}
}

void UC_BattleComponent::SetMode(EBattleMode InType)
{
	//if Same Type-> Unarmed
	if (Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false)
	{
		if (!!Datas[(int32)Type])
			Datas[(int32)Type]->GetEquipment()->Unequip();
	}

	if (!!Datas[(int32)Type])
		Datas[(int32)InType]->GetEquipment()->Equip();

	ChangeMode(InType);
}

void UC_BattleComponent::ChangeMode(EBattleMode InType)
{
	EBattleMode prevType = Type;
	Type = InType;

	if (OnBattleTypeChanged.IsBound())
		OnBattleTypeChanged.Broadcast(prevType, InType);

}
