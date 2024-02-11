#include "P_AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/NavMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UP_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	if (character == nullptr) return;
	UC_BattleComponent* battle = Cast<UC_BattleComponent>(character->GetComponentByClass(UC_BattleComponent::StaticClass()));
	if (battle == nullptr) return;

	battle->OnBattleTypeChanged.AddDynamic(this, &UP_AnimInstance::OnBattleTypeChanged);
}

void UP_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character == nullptr) return;
	Speed = Character->GetVelocity().Size2D();
	IsinAir = Character->GetMovementComponent()->IsFalling();
	Direction = CalculateDirection(Character->GetVelocity(),Character->GetControlRotation());

}

void UP_AnimInstance::OnBattleTypeChanged(EBattleMode InprevType, EBattleMode InType)
{
	//BattleType ->ABP to Change Animation
	BattleType = InType;
	
}
