#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_OptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELEMENTAL_API UC_OptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_OptionComponent();

protected:
	virtual void BeginPlay() override;


		
};
