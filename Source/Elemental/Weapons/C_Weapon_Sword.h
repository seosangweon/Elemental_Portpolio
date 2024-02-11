#pragma once

#include "CoreMinimal.h"
#include "../Datas/CWeapon.h"
#include "C_Weapon_Sword.generated.h"

UCLASS()
class ELEMENTAL_API AC_Weapon_Sword : public ACWeapon
{
	GENERATED_BODY()
	
public:	
	AC_Weapon_Sword();
	void AttachSocket(FName InName) override;
	void SetSwordVisible();

protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* MeshComp;

};
