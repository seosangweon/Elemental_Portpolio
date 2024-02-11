#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBattleData.h"
#include "C_Action.generated.h"

UCLASS()
class ELEMENTAL_API AC_Action : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Action();

	FORCEINLINE void SetDatas(TArray<FActionData> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetSkillDatas(TArray<FActionData> InDatas) { SkillDatas = InDatas; }


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Action() {};
	virtual void Begin_Action() {};
	virtual void Begin_Skill() {};
	virtual void End_Action() {};

	virtual void Skill01() {};
	virtual void Skill02() {};

	virtual void OnAim() {};
	virtual void OffAim() {};
	

	UFUNCTION()
		virtual void OnWeaponBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

	UFUNCTION()
		virtual void OnWeaponEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {};

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UC_StateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UC_BattleComponent* Battle;
public:
	class UBoxComponent* ActionBox;

protected:
	TArray<FActionData> Datas;
	TArray<FActionData> SkillDatas;
	

};
