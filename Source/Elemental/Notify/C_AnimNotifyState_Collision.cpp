#include "C_AnimNotifyState_Collision.h"
#include "../Datas/CWeapon.h"
#include "../Datas/CBattleData.h"
#include "../Datas/C_Action.h"
#include "../Datas/C_Action_Melee.h"
#include "../Components/C_BattleComponent.h"


FString UC_AnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UC_AnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp,Animation,TotalDuration);

	if (MeshComp == nullptr)return;
	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;
	battle->GetCurrentBattleType()->GetWeapon()->OnCollision();

}

void UC_AnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == nullptr)return;
	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr)return;
	battle->GetCurrentBattleType()->GetWeapon()->OffCollision();

	//Clear 
	AC_Action_Melee* melee =  Cast<AC_Action_Melee>(battle->GetCurrentBattleType()->GetAction());
	if (melee == nullptr) return;
	melee->ClearHittedCharacters();
}