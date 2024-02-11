#pragma once

#include "CoreMinimal.h"
#include "C_Action.h"
#include "C_Action_Magic.generated.h"

UCLASS()
class ELEMENTAL_API AC_Action_Magic : public AC_Action
{
	GENERATED_BODY()

public:
	AC_Action_Magic();

	virtual void BeginPlay() override;

	virtual void Action() override;
	virtual void Begin_Action() override;
	virtual void Begin_Skill() override;
	virtual void End_Action() override;

	virtual void Skill01() override;
	virtual void Skill02() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnAim() override;
	virtual void OffAim() override;
	
private:
	UFUNCTION()
		void OnMagicBeginOverlap(FHitResult InHitResult);
	UFUNCTION()
		void OnSkillBeginOverlap(FHitResult InHitResult);

	bool GetCursorLocation(FVector& OutLocation,FRotator& OutRotator);

public:
	int IsSpawn = 0;

private:
	UPROPERTY()
		class UCAim* Aim;

	class AC_Magic* Magic_object;
	class AC_AOSkill* SkillDecal;
	class UDecalComponent* Decal;
	class UBoxComponent* Box;

	FVector CursorLocation;
	FRotator CursorRotation;
};
