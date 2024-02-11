#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_BattleComponent.generated.h"

UENUM(BlueprintType)
enum class EBattleMode: uint8
{
	Unarmed, Sword, GreatSword,Magic, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBattleTypeChanged, EBattleMode, InprevType, EBattleMode, InType);

UCLASS()
class ELEMENTAL_API UC_BattleComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UC_BattleComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCBattleData* GetCurrentBattleType() { return Datas[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EBattleMode::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsSwordMode() { return Type == EBattleMode::Sword; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsGreatSwordMode() { return Type == EBattleMode::GreatSword; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsMagicMode() { return Type == EBattleMode::Magic; }

public:
	void SetUnarmedMode();
	void SetSwordMode();
	void SetGreatSwordMode();
	void SetMagicMode();

	void Action();

	void Skill01();
	void Skill02();

	void OnAim();
	void OffAim();

	void Dead();
	void End_Dead();

	void OffAllCollisions();

private:
	void SetMode(EBattleMode InType);
	void ChangeMode(EBattleMode InType);

public:
	UPROPERTY(BlueprintAssignable)
		FBattleTypeChanged OnBattleTypeChanged;
	
private: 
	EBattleMode Type;

	UPROPERTY(EditDefaultsOnly)
		class UCBattleData* Datas[(int32)EBattleMode::Max];
};
