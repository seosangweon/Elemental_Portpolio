#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CBattleData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;
};

USTRUCT(BlueprintType)
struct FActionData :public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Damage = 10.f;

	UPROPERTY(EditAnywhere)
		float HitStop;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AC_Magic> MagicClass;


};

/*
	Class----------------------------------------------------------------------
*/
UCLASS()
class ELEMENTAL_API UCBattleData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(class ACharacter* OwnerCharacter);

	FORCEINLINE class AC_Equipment* GetEquipment() {return Equipment ;}
	FORCEINLINE class ACWeapon* GetWeapon() {return Weapon;	}
	FORCEINLINE class AC_Action* GetAction() {return Action;}
	FORCEINLINE class AC_Action* GetSkill() {return Skill;}
	FORCEINLINE class AC_AOSkill* GetAOE() {return AOE;}


public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class AC_Equipment> EquipmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		TSubclassOf<class ACWeapon> WeaponClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Equipment")
		FEquipmentData EquipmentData;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Action")
		TSubclassOf<class AC_Action> ActionClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Action")
		TArray<FActionData> ActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill")
		TSubclassOf<class AC_Action> SkillClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill")
		TArray<FActionData> SkillDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AOE")
		TSubclassOf<class AC_AOSkill> AOEClass;

private:
	class AC_Equipment* Equipment;
	class ACWeapon* Weapon;
	class AC_Action* Action; 
	class AC_Action* Skill; 
	class AC_AOSkill* AOE;
};
