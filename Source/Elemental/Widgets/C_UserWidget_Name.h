#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UserWidget_Name.generated.h"

UCLASS()
class ELEMENTAL_API UC_UserWidget_Name : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetName(const FString& InName);
	
};
