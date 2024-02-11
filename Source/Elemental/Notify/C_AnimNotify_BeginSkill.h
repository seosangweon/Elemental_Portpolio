#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_AnimNotify_BeginSkill.generated.h"

UCLASS()
class ELEMENTAL_API UC_AnimNotify_BeginSkill : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(BlueprintReadOnly)
		class UC_BattleComponent* Battle;
};
