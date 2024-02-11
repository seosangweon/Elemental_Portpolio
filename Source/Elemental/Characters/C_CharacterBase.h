#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_CharacterBase.generated.h"

UCLASS()
class ELEMENTAL_API AC_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AC_CharacterBase();

protected:
	virtual void BeginPlay() override;



};
