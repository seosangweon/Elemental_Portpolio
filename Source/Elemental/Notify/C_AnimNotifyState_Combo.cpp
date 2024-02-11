#include "C_AnimNotifyState_Combo.h"
#include "../Datas/C_Action_Melee.h"
#include "../Components/C_BattleComponent.h"

FString UC_AnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UC_AnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp == nullptr) return;

	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;

	AC_Action_Melee* melee = Cast<AC_Action_Melee>(battle->GetCurrentBattleType()->GetAction());
	if (melee == nullptr)return;
	melee->EnableCombo();

}
void UC_AnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;

	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;

	AC_Action_Melee* melee = Cast<AC_Action_Melee>(battle->GetCurrentBattleType()->GetAction());
	if (melee == nullptr)return;
	melee->DisableCombo();
}