#include "CNotify_Idle.h"
#include "../Characters/C_Player.h"

FString UCNotify_Idle::GetNotifyName_Implementation() const
{
	return "SetIdle";
}

void UCNotify_Idle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr)
		return;

	UC_StateComponent* state = Cast<UC_StateComponent>(MeshComp->GetOwner()->GetComponentByClass(UC_StateComponent::StaticClass()));
	if (state == nullptr) return;

	state->SetIdleState();
	
	AC_Player* player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == nullptr) return;
	player->State->SetIdleState();
	player->End_Roll();
}
