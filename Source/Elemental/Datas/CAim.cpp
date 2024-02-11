#include "CAim.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

UCAim::UCAim()
{
	
}

void UCAim::BeginPlay(class ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;
	SpringArm = Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	Camera = Cast<UCameraComponent>(OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));

}

void UCAim::Tick(float DeltaTime)
{

}

void UCAim::On()
{
	if (IsAvaliable() == false) return;
	if (bZoomIn == true) return;
	bZoomIn = true;
	
	SpringArm->TargetArmLength = 700.f;
	//SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;
}

void UCAim::Off()
{
	if (IsAvaliable() == false) return;
	if (bZoomIn == false) return;
	bZoomIn = false;

	SpringArm->TargetArmLength = 400.f;
	//SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;
}
