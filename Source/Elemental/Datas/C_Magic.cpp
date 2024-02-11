#include "C_Magic.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AC_Magic::AC_Magic()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Sphere);
		
	Projectile = this->CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	
	Projectile->InitialSpeed = 3000.f;
	Projectile->MaxSpeed = 6000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = true;

	InitialLifeSpan = 3.f;
}

void AC_Magic::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AC_Magic::OnComponentBeginOverlap);
}

void AC_Magic::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;
	//Sweep 
	if (!!ImpactParticle)
	{
		FTransform transform = ImpactParticleTransform;
		transform.AddToTranslation(bFromSweep ? SweepResult.Location : GetActorLocation());
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle,transform);
	}

	//Damage
	if (OnMagicBeginOverlap.IsBound())
		OnMagicBeginOverlap.Broadcast(SweepResult);

	Destroy();
}

