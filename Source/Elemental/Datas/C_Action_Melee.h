#pragma once

#include "CoreMinimal.h"
#include "C_Action.h"
#include "C_Action_Melee.generated.h"

UCLASS()
class ELEMENTAL_API AC_Action_Melee : public AC_Action
{
	GENERATED_BODY()

public:
	virtual void Action() override;
	virtual void Begin_Action() override;
	virtual void Begin_Skill() override;
	virtual void End_Action() override;

	virtual void Skill01() override;
	virtual void Skill02() override;

	virtual void OnWeaponBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnWeaponEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;



public:
	FORCEINLINE void EnableCombo() { bCanCombo = true; }
	FORCEINLINE void DisableCombo() { bCanCombo = false; }
	FORCEINLINE void ClearHittedCharacters() { HittedCharacters.Empty(); }

private:
	int32 ComboCount;
	bool bCanCombo;
	bool bSucceed;

	TArray<class ACharacter*> HittedCharacters;
};
