#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Components/C_StateComponent.h"
#include "I_Character.h"
#include "C_Player.generated.h"

UCLASS()
class ELEMENTAL_API AC_Player : public ACharacter , public II_Character
{
	GENERATED_BODY()

public:
	AC_Player();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UFUNCTION()
	void OnForward(float AxisValue);
	UFUNCTION()
	void OnRight(float AxisValue);

	UFUNCTION()
		void OnHorizontal(float AxisValue);
	UFUNCTION()
		void OnVertical(float AxisValue);

	UFUNCTION()
		void OnZoom(float AxisValue);
	UFUNCTION()  
		void Walk();
	UFUNCTION()
		void Evade();

	UFUNCTION()  
		void Sword();	
	UFUNCTION()
		void GreatSword();
	UFUNCTION()
		void Magic();
	UFUNCTION()
		void OnAction();

	UFUNCTION()
		void OnSkill01();
	UFUNCTION()
		void OnSkill02();
	UFUNCTION()
		void TargetFix();

	void OnAim();
	void OffAim();

public:
	void GetTargetAtTrace();

	void GetTargetEnemy();

private:
	UFUNCTION()
		void OnStateChanged(ECurrentState InprevState, ECurrentState InState);

	void PlayRoll();
	void Begin_Roll();
public:
	void End_Roll();

	UFUNCTION(BlueprintCallable)
		TArray<AC_Enemy*> GetEnemyObjectReferecne();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UC_AnimComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class UC_BattleComponent* Battle;


public:
	UPROPERTY(VisibleDefaultsOnly)
		class UC_StateComponent* State;

	// Inherited via II_Character
	virtual void ChangeColor(FLinearColor InColor);

public:
	float TargetDistance = 1500.f;
	class TArray<AC_Enemy*> Enemies;
	class AC_Enemy* Enemy;
	class AC_Enemy* TargetEnemy;
	
private:
	class UMaterialInstanceDynamic* DynamicMat;
	//class AC_AOSkill* SkillDecal;
	//class UBoxComponent* SkillBox;
	//class AC_Weapon_Sword* WeaponSword;

};
