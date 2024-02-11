#include "C_Action_Magic.h"
#include "CAim.h"
#include "../Components/C_StateComponent.h"
#include "../Components/C_BattleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "CWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C_Magic.h"
#include "C_AOSkill.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"

AC_Action_Magic::AC_Action_Magic()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_Action_Magic::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
}

void AC_Action_Magic::Action()
{
	Super::Action();

	if (State->IsStateIdle() == false) return;
		State->SetActionState();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? State->SetMove() : State->SetStop();
}

void AC_Action_Magic::Begin_Action()
{
	Super::Begin_Action();
	
	FVector socket_location = OwnerCharacter->GetMesh()->GetSocketLocation("Magic_Socket");
	FRotator rotation = OwnerCharacter->GetController()->GetControlRotation();

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(socket_location);
	transform.SetRotation(FQuat(rotation));

	//Spawn Magic
	Magic_object = GetWorld()->SpawnActorDeferred<AC_Magic>(Datas[0].MagicClass, transform, OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Magic_object->OnMagicBeginOverlap.AddDynamic(this, &AC_Action_Magic::OnMagicBeginOverlap);
	UGameplayStatics::FinishSpawningActor(Magic_object, transform);
	
}
void AC_Action_Magic::Begin_Skill()
{
	Super::Begin_Skill();

	FRotator rotation;
	if (GetCursorLocation(CursorLocation, rotation) == false) return;
	

	//Spawn Skill Effect
	if (UKismetMathLibrary::Vector_Distance(OwnerCharacter->GetActorLocation(), CursorLocation) < 1500)
	{
		if (State->IsSkill01()){
			FTransform transform = SkillDatas[0].EffectTransform;
			transform.AddToTranslation(CursorLocation);
			UGameplayStatics::SpawnEmitterAtLocation(OwnerCharacter->GetWorld(), SkillDatas[0].Effect, transform);
		}
		else if(State->IsSkill01() == false){
			FTransform transform = SkillDatas[1].EffectTransform;
			transform.AddToTranslation(CursorLocation);
			UGameplayStatics::SpawnEmitterAtLocation(OwnerCharacter->GetWorld(), SkillDatas[1].Effect, transform);
		}
	}
}


void AC_Action_Magic::End_Action()
{
	Super::End_Action();
	State->SetIdleState();
	State->SetMove();
}

void AC_Action_Magic::Skill01()
{
	Super::Skill01();

	if (SkillDatas.Num() > 0 == false) return;
	if (State->IsStateIdle() == false) return;
	State->SetActionState();
	if (Aim->IsAvaliable() == false) return;
	State->SetSkill01();

	OwnerCharacter->PlayAnimMontage(SkillDatas[0].AnimMontage, SkillDatas[0].PlayRate, SkillDatas[0].StartSection);
	SkillDatas[0].bCanMove ? State->SetMove() : State->SetStop();
}

void AC_Action_Magic::Skill02()
{
	Super::Skill02();

	if (SkillDatas.Num() > 0 == false) return;
	if (State->IsStateIdle() == false) return;
	State->SetActionState();
	if (Aim->IsAvaliable() == false) return;

	State->SetSkill02();
	OwnerCharacter->PlayAnimMontage(SkillDatas[1].AnimMontage, SkillDatas[1].PlayRate, SkillDatas[1].StartSection);
	SkillDatas[1].bCanMove ? State->SetMove() : State->SetStop();
}

void AC_Action_Magic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ownerLocation;
	ownerLocation = OwnerCharacter->GetActorLocation();

	//Cursor On World Statics
	if (GetCursorLocation(CursorLocation, CursorRotation))
	{
		FTransform transform;
		transform.AddToTranslation(CursorLocation);
	
		if (!!Box)
		{
			if (UKismetMathLibrary::Vector_Distance(ownerLocation, CursorLocation) < 1500)
			{
				Box->SetWorldLocation(CursorLocation);
				//SkillDecal->SetActorLocation(CursorLocation);
			}
			else
			{
				Decal->SetVisibility(false);
			}
		}
	}
}

void AC_Action_Magic::OnAim()
{
	if (IsSpawn == 0)
	{
		for (AActor* actor : OwnerCharacter->Children)
		{
			if (actor->IsA<AC_AOSkill>() && actor->GetActorLabel().Contains("AOSkill"))
			{
				SkillDecal = Cast<AC_AOSkill>(actor);
				Decal = Cast<UDecalComponent>(actor->GetComponentByClass(UDecalComponent::StaticClass()));
				Box = Cast<UBoxComponent>(actor->GetComponentByClass(UBoxComponent::StaticClass()));
				break;
			}
			IsSpawn = IsSpawn + 1;
		}
	}
	SkillDecal->OnSkillBeginOverlap.AddDynamic(this, &AC_Action_Magic::OnSkillBeginOverlap);
	Aim->On();
	Decal->SetVisibility(true);
}

void AC_Action_Magic::OffAim()
{
	Aim->Off();
	Decal->SetVisibility(false);
}

void AC_Action_Magic::OnMagicBeginOverlap(FHitResult InHitResult)
{
	FDamageEvent de;

	InHitResult.GetActor()->TakeDamage(Datas[0].Damage,de,OwnerCharacter->GetController(), Magic_object);
}

void AC_Action_Magic::OnSkillBeginOverlap(FHitResult InHitResult)
{
	FDamageEvent de;

	if (State->IsSkill01()){
		InHitResult.GetActor()->TakeDamage(30.f, de, OwnerCharacter->GetController(), OwnerCharacter);
	}
	else if(State->IsSkill01()==false) {
		InHitResult.GetActor()->TakeDamage(40.f, de, OwnerCharacter->GetController(), OwnerCharacter);
	}
}

bool AC_Action_Magic::GetCursorLocation(FVector& OutLocation, FRotator& OutRotator)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//World Static
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery1);
	
	FHitResult hitResult;
	if (controller->GetHitResultUnderCursorForObjects(objects, false, hitResult))
	{
		OutLocation = hitResult.Location;
		OutRotator = hitResult.ImpactNormal.Rotation();
		return true;
	}
	return false;
}

