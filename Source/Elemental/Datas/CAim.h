#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAim.generated.h"

UCLASS()
class ELEMENTAL_API UCAim : public UObject
{
	GENERATED_BODY()
	
public:
	UCAim(); 

	void BeginPlay(class ACharacter* InOwnerCharacter);
	void Tick(float DeltaTime);

public:
	FORCEINLINE bool IsAvaliable() { return SpringArm != nullptr && Camera != nullptr; }
	FORCEINLINE bool IsZooming() { return bZoomIn ; }

	void On();
	void Off();

private:
	class ACharacter* OwnerCharacter;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

public:
	bool bZoomIn ;
	
}; 
