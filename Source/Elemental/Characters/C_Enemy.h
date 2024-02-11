#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "I_Character.h"
#include "../Components/C_StateComponent.h"
#include "C_Enemy.generated.h"

UCLASS()
class ELEMENTAL_API AC_Enemy : public ACharacter ,public II_Character
{
	GENERATED_BODY()

public:
	AC_Enemy();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

public:
	void ChangeColor(FLinearColor InColor)override;

private:
	void Hit();
	void Dead();
	UFUNCTION()
		void End_Dead();

	UFUNCTION()
		void ResetColor();

private:
	UFUNCTION()
		void OnStateChanged(ECurrentState InprevState, ECurrentState InState);

private:
	UPROPERTY(EditAnywhere)
		float LaunchValue = 20.f;
	UPROPERTY(EditAnywhere)
		float ForceValue = 333333.f;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UC_BattleComponent* Battle;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_AnimComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class UC_StateComponent* State;

private:
	class UMaterialInstanceDynamic* DynamicMat;

	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;
};
