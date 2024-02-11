#include "C_AnimNotifyState_AOECollision.h"
#include "../Datas/C_AOSkill.h"
#include "../Datas/CBattleData.h"
#include "../Datas/C_Action.h"
#include "../Datas/C_Action_Melee.h"
#include "../Components/C_BattleComponent.h"


FString UC_AnimNotifyState_AOECollision::GetNotifyName_Implementation() const
{
	return "AOECollision";
}

void UC_AnimNotifyState_AOECollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp,Animation,TotalDuration);

	if (MeshComp == nullptr)return;
	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;
	battle->GetCurrentBattleType()->GetAOE()->OnCollision();

}

void UC_AnimNotifyState_AOECollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == nullptr)return;
	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;
	battle->GetCurrentBattleType()->GetAOE()->OffCollision();

}