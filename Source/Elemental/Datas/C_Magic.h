#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Magic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMagicBeginOverlap, FHitResult, InHitResult);

UCLASS()
class ELEMENTAL_API AC_Magic : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Magic();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly)
		FTransform ImpactParticleTransform;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

public:
	UPROPERTY(BlueprintAssignable)
		FMagicBeginOverlap OnMagicBeginOverlap;
}; 
