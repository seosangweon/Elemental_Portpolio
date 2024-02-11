#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UserWidget_Health.generated.h"

UCLASS()
class ELEMENTAL_API UC_UserWidget_Health : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(float InHealth, float InMaxHealth);
	
};
