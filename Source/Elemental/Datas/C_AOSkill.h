#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_AOSkill.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillBeginOverlap, FHitResult, InHitResult);

UCLASS()
class ELEMENTAL_API AC_AOSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_AOSkill();

	void OnCollision();
	void OffCollision();

public:
	FORCEINLINE class USceneComponent* GetSceneComponent() { return Scene; }

protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UDecalComponent* Decal;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

public:
	UPROPERTY(BlueprintAssignable)
		FSkillBeginOverlap OnSkillBeginOverlap;
};
