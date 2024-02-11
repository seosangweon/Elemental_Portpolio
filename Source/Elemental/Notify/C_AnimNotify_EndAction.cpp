#include "C_AnimNotify_EndAction.h"
#include "GameFramework/Character.h"
#include "../Components/C_BattleComponent.h"
#include "../Datas/CBattleData.h"
#include "../Datas/C_Action.h"

FString UC_AnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UC_AnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr)return;
	MeshComp->GetOwner();
	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;
	battle->GetCurrentBattleType()->GetAction()->End_Action();

}