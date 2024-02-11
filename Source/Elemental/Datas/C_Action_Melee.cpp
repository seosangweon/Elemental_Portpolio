#include "C_Action_Melee.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "../Components/C_StateComponent.h"
#include "../Components/C_BattleComponent.h"

void AC_Action_Melee::Action()
{
	Super::Action();
	if (Datas.Num() > 0 == false) return;

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;

		return;
	}
	
	if (State->IsStateIdle() == false) return;
	State->SetActionState();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,Datas[0].PlayRate,Datas[0].StartSection);
	Datas[0].bCanMove ? State->SetMove() : State->SetStop();
}

void AC_Action_Melee::Begin_Action()
{
	Super::Begin_Action();

	if (bSucceed == false) return;
	bSucceed = false;

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? State->SetMove() : State->SetStop();

}

void AC_Action_Melee::Begin_Skill()
{
	Super::Begin_Skill();


}

void AC_Action_Melee::End_Action()
{
	Super::End_Action();

	ComboCount = 0;
	OwnerCharacter->StopAnimMontage();
	
	State->SetIdleState();
	State->SetMove();
}

void AC_Action_Melee::Skill01()
{
	Super::Skill01();
	
	if (SkillDatas.Num() > 0 == false) return;
	if (State->IsStateIdle() == false) return;
	State->SetSkillState();
	State->SetSkill01();

	OwnerCharacter->PlayAnimMontage(SkillDatas[0].AnimMontage, SkillDatas[0].PlayRate, SkillDatas[0].StartSection);
	SkillDatas[0].bCanMove ? State->SetMove() : State->SetStop();
}

void AC_Action_Melee::Skill02()
{
	Super::Skill02();
	
	if (SkillDatas.Num() > 0 == false) return;
	if (State->IsStateIdle() == false) return;
	State->SetSkillState();
	State->SetSkill02();

	OwnerCharacter->PlayAnimMontage(SkillDatas[1].AnimMontage, SkillDatas[1].PlayRate, SkillDatas[1].StartSection);
	SkillDatas[1].bCanMove ? State->SetMove() : State->SetStop();
}

void AC_Action_Melee::OnWeaponBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnWeaponBeginOverlap(InAttacker, InCauser, InOtherCharacter);
	
	SkillDatas = Battle->GetCurrentBattleType()->SkillDatas;
		int32 hittedCharactersNum = HittedCharacters.Num();
		HittedCharacters.AddUnique(InOtherCharacter);

	if (State->IsStateAction())
	{
		//OnWeaponBeginOverlap Particle
		UParticleSystem* hitEffect = Datas[ComboCount].Effect;
		if (!!hitEffect)
		{
			FTransform transform = Datas[ComboCount].EffectTransform;
			transform.AddToTranslation(InOtherCharacter->GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
		}

		//OnWeaponBeginOverlap Camera Shake
		TSubclassOf<UCameraShake> shake = Datas[ComboCount].ShakeClass;
		if (!!shake)
		{
			APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			controller->PlayerCameraManager->PlayCameraShake(shake);
		}

		if (hittedCharactersNum < HittedCharacters.Num())
		{
			FDamageEvent damageevent;
			InOtherCharacter->TakeDamage(Datas[ComboCount].Damage, damageevent, InAttacker->GetController(), InCauser);
		}
	}
	else if (State->IsStateSkill())
	{
		GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, TEXT("d"));
		if (State->IsSkill01() == true)
		{
			UParticleSystem* hitEffect = SkillDatas[0].Effect;
			if (!!hitEffect)
			{
				FTransform transform = SkillDatas[0].EffectTransform;
				transform.AddToTranslation(InOtherCharacter->GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
			}
			TSubclassOf<UCameraShake> shake = SkillDatas[0].ShakeClass;
			if (!!shake)
			{
				APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				controller->PlayerCameraManager->PlayCameraShake(shake);
			}
			if (hittedCharactersNum < HittedCharacters.Num())
			{
				FDamageEvent damageevent;
				InOtherCharacter->TakeDamage(SkillDatas[0].Damage, damageevent, InAttacker->GetController(), InCauser);
			}
		}
		else if (State->IsSkill01() == false)
		{
			UParticleSystem* hitEffect = SkillDatas[1].Effect;
			if (!!hitEffect)
			{
				FTransform transform = SkillDatas[1].EffectTransform;
				transform.AddToTranslation(InOtherCharacter->GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
			}
			TSubclassOf<UCameraShake> shake = SkillDatas[1].ShakeClass;
			if (!!shake)
			{
				APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				controller->PlayerCameraManager->PlayCameraShake(shake);
			}
			if (hittedCharactersNum < HittedCharacters.Num())
			{
				FDamageEvent damageevent;
				InOtherCharacter->TakeDamage(SkillDatas[1].Damage, damageevent, InAttacker->GetController(), InCauser);
			}
		}
	}
}

void AC_Action_Melee::OnWeaponEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnWeaponEndOverlap(InAttacker, InCauser, InOtherCharacter);

}
