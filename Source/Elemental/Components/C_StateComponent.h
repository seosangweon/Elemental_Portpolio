#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_StateComponent.generated.h"

UENUM(BlueprintType)
enum class ECurrentState: uint8
{
	Idle, Roll,Equip, Action,Skill,Hit,Dead, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateChanged, ECurrentState, InprevState, ECurrentState, InState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTAL_API UC_StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_StateComponent();
	
public:
	FORCEINLINE bool IsCanMove()		{ return bCanMove; }
	FORCEINLINE bool IsSkill01()		{ return bSkill; }
	FORCEINLINE float GetWalkSpeed()	{ return WalkSpeed;}
	FORCEINLINE float GetRunSpeed()		{ return RunSpeed;}
	FORCEINLINE float GetHealth()		{ return Health;}
	FORCEINLINE float GetMaxHealth()	{ return MaxHealth;}

public:
	FORCEINLINE bool IsStateIdle() {return State == ECurrentState::Idle; }
	FORCEINLINE bool IsStateRoll() {return State == ECurrentState::Roll; }
	FORCEINLINE bool IsStateEquip() {return State == ECurrentState::Equip; }
	FORCEINLINE bool IsStateAction() {return State == ECurrentState::Action; }
	FORCEINLINE bool IsStateSkill() {return State == ECurrentState::Skill; }
	FORCEINLINE bool IsStateHit() {return State == ECurrentState::Hit; }
	FORCEINLINE bool IsStateDead() {return State == ECurrentState::Dead; }

	void SetIdleState();
	void SetRollState();
	void SetEquipState();
	void SetActionState();
	void SetSkillState();
	void SetHitState();
	void SetDeadState();

	void SetMove();
	void SetStop();
	void SetSkill01();
	void SetSkill02();

	void DecreaseHealth(float InValue);
	void IncreaseHealth(float InValue);

private:
	void ChangeState(ECurrentState InState);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
		float WalkSpeed = 250;

	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
		float RunSpeed = 600;

	float Health;

	bool bCanMove = true;
	bool bSkill;

public:
	UPROPERTY(BlueprintAssignable)
		FStateChanged OnStateChanged;

private:
		ECurrentState State;
};
