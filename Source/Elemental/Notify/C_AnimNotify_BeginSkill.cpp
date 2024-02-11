#include "C_AnimNotify_BeginSkill.h"
#include "GameFramework/Character.h"
#include "../Components/C_BattleComponent.h"
#include "../Datas/CBattleData.h"
#include "../Datas/C_Action.h"

FString UC_AnimNotify_BeginSkill::GetNotifyName_Implementation() const
{
	return "BeginSkill";
}

void UC_AnimNotify_BeginSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr)return;

	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;
	battle->GetCurrentBattleType()->GetSkill()->Begin_Skill();
	
}
