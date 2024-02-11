#include "C_StateComponent.h"

UC_StateComponent::UC_StateComponent()
{

}

void UC_StateComponent::SetIdleState()
{
	ChangeState(ECurrentState::Idle);
}

void UC_StateComponent::SetRollState()
{
	ChangeState(ECurrentState::Roll);
}

void UC_StateComponent::SetEquipState()
{
	ChangeState(ECurrentState::Equip);
}

void UC_StateComponent::SetActionState()
{
	ChangeState(ECurrentState::Action);
}
void UC_StateComponent::SetSkillState()
{
	ChangeState(ECurrentState::Skill);
}


void UC_StateComponent::SetHitState()
{
	ChangeState(ECurrentState::Hit);
}

void UC_StateComponent::SetDeadState()
{
	ChangeState(ECurrentState::Dead);
}

void UC_StateComponent::SetMove()
{
	bCanMove = true;
}

void UC_StateComponent::SetStop()
{
	bCanMove = false;
}

void UC_StateComponent::SetSkill01()
{
	bSkill = true;
}

void UC_StateComponent::SetSkill02()
{
	bSkill = false;
}


void UC_StateComponent::DecreaseHealth(float InValue)
{
	Health -= InValue;

	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

void UC_StateComponent::IncreaseHealth(float InValue)
{
	Health += InValue;

	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

void UC_StateComponent::ChangeState(ECurrentState InState)
{
	//Set prev Before Change
	ECurrentState prevState = State; 
	State = InState; //Set CurrentState

	if (OnStateChanged.IsBound())
		OnStateChanged.Broadcast(prevState, State);
}

void UC_StateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	
}


