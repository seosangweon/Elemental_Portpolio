#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "C_StateComponent.h"
#include "C_AnimComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontage : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ECurrentState State;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		bool bCanMove;
};

UCLASS()
class ELEMENTAL_API UC_AnimComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UC_AnimComponent();


	void PlayHit();
	void PlayDead();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

public:
	void PlayAnimMontage(ECurrentState InState);
private:
	FMontage* Montages[(int32)ECurrentState::Max];

};
