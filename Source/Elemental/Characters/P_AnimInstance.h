#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Components/C_BattleComponent.h"
#include "P_AnimInstance.generated.h"

UCLASS()
class ELEMENTAL_API UP_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsinAir;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EBattleMode BattleType;

private:
	UFUNCTION()
		void OnBattleTypeChanged(EBattleMode InprevType, EBattleMode InType);

private:
	class ACharacter* Character;
};