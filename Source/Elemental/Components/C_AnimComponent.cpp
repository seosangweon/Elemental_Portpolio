#include "C_AnimComponent.h"
#include "GameFramework/Character.h"

UC_AnimComponent::UC_AnimComponent()
{

}

void UC_AnimComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
		return;
	
	TArray<FMontage*> montages; 
	DataTable->GetAllRows<FMontage>("", montages);

	for (int32 i = 0; i < (int32)ECurrentState::Max; i++)
	{
		for (FMontage* data : montages)
		{
			if ((ECurrentState)i == data->State)
			{
				Montages[i] = data;
				continue;
			}
		}
	}
}

void UC_AnimComponent::PlayAnimMontage(ECurrentState InState)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (character == nullptr)
		return;

	const FMontage* animData = Montages[(int32)InState];

	if (!!animData)
	{
		if(!!animData->AnimMontage)
		character->PlayAnimMontage(animData->AnimMontage, animData->PlayRate, animData->StartSection);
	}

}

void UC_AnimComponent::PlayHit()
{
	PlayAnimMontage(ECurrentState::Hit);
}

void UC_AnimComponent::PlayDead()
{
	PlayAnimMontage(ECurrentState::Dead);
}
