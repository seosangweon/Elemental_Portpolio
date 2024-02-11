#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Character.generated.h"

UINTERFACE(MinimalAPI)
class UI_Character : public UInterface
{
	GENERATED_BODY()
};

class ELEMENTAL_API II_Character
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(FLinearColor InColor) = 0;
};
