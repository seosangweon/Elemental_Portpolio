#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWeaponBeginOverlap, class ACharacter*, InAttacker,class AActor* , InCauser, class ACharacter*,InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWeaponEndOverlap, class ACharacter*, InAttacker,class AActor* , InCauser, class ACharacter*,InOtherCharacter);

UCLASS()
class ELEMENTAL_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

	void OnCollision();
	void OffCollision();

	UFUNCTION(BlueprintCallable)
	virtual void AttachSocket(FName InName);

	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

protected:
	virtual void BeginPlay() override;


protected:

	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UC_StateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UC_BattleComponent* Battle;
public:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(BlueprintAssignable)
		FWeaponBeginOverlap OnWeaponBeginOverlap;
	UPROPERTY(BlueprintAssignable)
		FWeaponEndOverlap OnWeaponEndOverlap;

private:
	TArray<class UShapeComponent*> ShapeComponents;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
