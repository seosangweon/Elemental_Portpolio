#include "C_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "../Components/C_AnimComponent.h"
#include "../Components/C_BattleComponent.h"
#include "Camera/CameraComponent.h"
#include "P_AnimInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../Datas/CWeapon.h"
#include "../Weapons/C_Weapon_Sword.h"
#include "../Datas/C_AOSkill.h"
#include "C_Enemy.h"
#include "Containers/Array.h"

AC_Player::AC_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Battle = CreateDefaultSubobject<UC_BattleComponent>("Battle");
	Montages = CreateDefaultSubobject<UC_AnimComponent>("Motages");
	State = CreateDefaultSubobject<UC_StateComponent>("State");


	ConstructorHelpers::FObjectFinder<USkeletalMesh>playerMesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Barbarous.SK_CharM_Barbarous'"));
	if (playerMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(playerMesh.Object);

	ConstructorHelpers::FClassFinder<UP_AnimInstance>abpClass(TEXT("AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'"));
	if (abpClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(abpClass.Class);
	

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));

	SpringArm->SetRelativeLocation(FVector(0,0,88));
	SpringArm->bUsePawnControlRotation = true; //Pitch Rotation
	SpringArm->bEnableCameraLag = true;
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 550;
	GetCharacterMovement()->AirControl = 0.1f;
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);

}

void AC_Player::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* mat = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(),nullptr,TEXT("MaterialInstanceConstant'/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Barbarous/M_Char_Barbrous_Inst.M_Char_Barbrous_Inst'")));
	DynamicMat = UMaterialInstanceDynamic::Create(mat, nullptr);
	GetMesh()->SetMaterial(0, DynamicMat);
	//DynamicMat->SetVectorParameterValue("HitColor", FLinearColor(1, 0, 0, 0));

	State->OnStateChanged.AddDynamic(this, &AC_Player::OnStateChanged);
	Battle->SetUnarmedMode();


	
}

void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Forward",this,&AC_Player::OnForward);
	PlayerInputComponent->BindAxis("Right",this,&AC_Player::OnRight);
	PlayerInputComponent->BindAxis("HorizontalLook",this,&AC_Player::OnHorizontal);
	PlayerInputComponent->BindAxis("VerticalLook",this,&AC_Player::OnVertical);
	PlayerInputComponent->BindAxis("Zoom", this, &AC_Player::OnZoom);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AC_Player::Walk);
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &AC_Player::Evade);

	PlayerInputComponent->BindAction("Sword", IE_Pressed, this, &AC_Player::Sword);
	PlayerInputComponent->BindAction("GreatSword", IE_Pressed, this, &AC_Player::GreatSword);
	PlayerInputComponent->BindAction("Magic", IE_Pressed, this, &AC_Player::Magic);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AC_Player::OnAction);

	PlayerInputComponent->BindAction("Skill01", IE_Pressed, this, &AC_Player::OnSkill01);
	PlayerInputComponent->BindAction("Skill02", IE_Pressed, this, &AC_Player::OnSkill02);

	PlayerInputComponent->BindAction("TargetFix", IE_Pressed, this, &AC_Player::TargetFix);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AC_Player::OnAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AC_Player::OffAim);
}


void AC_Player::OnForward(float AxisValue)
{
	if (State->IsCanMove())
	{
		FRotator rotation = FRotator(0, GetControlRotation().Yaw, 0);
		FVector direction = FQuat(rotation).GetForwardVector().GetSafeNormal2D();
		AddMovementInput(direction, AxisValue);
	}
}

void AC_Player::OnRight(float AxisValue)
{
	if (State->IsCanMove())
	{
		FRotator rotation = FRotator(0, GetControlRotation().Yaw, 0);
		FVector direction = FQuat(rotation).GetRightVector().GetSafeNormal2D();
		AddMovementInput(direction, AxisValue);
	}
}

void AC_Player::OnHorizontal(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AC_Player::OnVertical(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AC_Player::OnZoom(float AxisValue)
{
	float armLimit = AxisValue * 30 + SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = UKismetMathLibrary::FClamp(armLimit, 150, 700);
}

void AC_Player::Sword()
{
	//Only Change StateIdle
	if (!State->IsStateIdle()) return;
	Battle->SetSwordMode(); 
}

void AC_Player::GreatSword()
{
	if (!State->IsStateIdle()) return;
	Battle->SetGreatSwordMode();
}

void AC_Player::Magic()
{
	if (!State->IsStateIdle()) return;
	Battle->SetMagicMode();
}

void AC_Player::OnAction()
{
	Battle->Action();
}

void AC_Player::OnSkill01()
{
	Battle->Skill01();
}

void AC_Player::OnSkill02()
{
	Battle->Skill02();
}

void AC_Player::TargetFix()
{
	GetTargetAtTrace();
}
 
void AC_Player::OnAim()
{
	Battle->OnAim();
}

void AC_Player::OffAim()
{
	Battle->OffAim();
}

void AC_Player::GetTargetAtTrace()
{
	FVector end = GetActorLocation();
	UKismetMathLibrary::Add_VectorFloat(end,1.f);

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery8);

	TArray<FHitResult> hitresults;
	TArray<AActor*> actorsIgnore;
	
	bool result = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),GetActorLocation(), end, TargetDistance, objects,false, actorsIgnore,EDrawDebugTrace::ForDuration, hitresults,true);
	if (result == true)
	{
		for (int32 Index = 0; Index < hitresults.Num(); Index++)
		{
			FHitResult hitresult = hitresults[Index];	
			Enemy = Cast<AC_Enemy>(hitresult.Actor);
			Enemies.AddUnique(Enemy);
			//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, Enemy->GetName());
			
		}
	}
}

void AC_Player::GetTargetEnemy()
{
	for (int32 Index = 0; Index < Enemies.Num(); Index++)
	{
		float Maximum;
		if (GetDotProductTo(Enemies[Index]) >= Maximum)
		{
			Maximum = GetDotProductTo(Enemies[Index]);
			AC_Enemy* target = Enemies[Index];
			
			if (!!target)
			{
				TargetEnemy = target;
				//TODO : Enemy에게 Target Cursor Widget 컴포넌트 부착하고 Forward Target이 유효하면 Lock On Enemy에서 위젯 visibility 켜기
			}
			else if (!target)
			{

			}
		}
		
	}
	
}

//TArray<AC_Enemy*> AC_Player::GetEnemyObjectReferecne()
//{
//		TArray<FHitResult> hitresults;
//	for (int32 Index = 0; Index < hitresults.Num(); Index++)
//	{
//		FHitResult hitresult = hitresults[Index];
//		
//		Enemy = Cast<AC_Enemy>(hitresult.GetActor());
//		//TArray<AC_Enemy>a;
//		Enemies.AddUnique(Enemy);
//	}
//		return Enemies;
//}

void AC_Player::Walk()
{
	//Run-> Walk
	if (GetCharacterMovement()->MaxWalkSpeed > State->GetWalkSpeed())
			GetCharacterMovement()->MaxWalkSpeed = State->GetWalkSpeed();
	//Walk -> Run
	else
		GetCharacterMovement()->MaxWalkSpeed = State->GetRunSpeed();
}

void AC_Player::Evade()
{
	if (!State->IsStateIdle())
		return; 
	if (!State->IsCanMove())
		return;

	State->SetRollState();
}

void AC_Player::OnStateChanged(ECurrentState InprevState, ECurrentState InState)
{
	switch (InState)	
	{
	case ECurrentState::Roll:
		Begin_Roll();
		break;
	}
}

void AC_Player::PlayRoll()
{
	Montages->PlayAnimMontage(ECurrentState::Roll);
}

void AC_Player::Begin_Roll()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	FVector start = GetActorLocation();
	FVector end = start + GetVelocity().GetSafeNormal2D();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, end));
	 
	PlayRoll();
}


void AC_Player::End_Roll()
{
	if (Battle->IsUnarmedMode() == false)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		bUseControllerRotationYaw = true;
	}

	State->SetIdleState();
}



void AC_Player::ChangeColor(FLinearColor InColor)
{

}
