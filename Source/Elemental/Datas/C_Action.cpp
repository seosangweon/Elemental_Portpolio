#include "C_Action.h"
#include "../Components/C_StateComponent.h"
#include "../Components/C_BattleComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

AC_Action::AC_Action()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_Action::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = Cast<UC_StateComponent>(OwnerCharacter->GetComponentByClass(UC_StateComponent::StaticClass()));
	Battle = Cast<UC_BattleComponent>(OwnerCharacter->GetComponentByClass(UC_BattleComponent::StaticClass()));
	Super::BeginPlay();

	
}


void AC_Action::Tick(float DeltaTime)
{

}
