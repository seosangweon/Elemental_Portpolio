#include "C_AnimNotifyState_Equip.h"
#include "../Components/C_BattleComponent.h"
#include "GameFramework/Character.h"
#include "../Datas/CBattleData.h"
#include "../Datas/C_Equipment.h"
#include "../Datas/CWeapon.h"

FString UC_AnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UC_AnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp == nullptr) return;

	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr) return;

	battle->GetCurrentBattleType()->GetEquipment()->Begin_Equip();
}

void UC_AnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;

	UC_BattleComponent* battle = Cast<UC_BattleComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr) return;

	battle->GetCurrentBattleType()->GetEquipment()->End_Equip();


}
