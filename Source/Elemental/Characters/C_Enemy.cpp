#include "C_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Components/C_AnimComponent.h"
#include "../Components/C_BattleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "P_AnimInstance.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Widgets/C_UserWidget_Health.h"
#include "../Widgets/C_UserWidget_Name.h"
#include "Kismet/KismetSystemLibrary.h"

AC_Enemy::AC_Enemy()
{
	NameWidget = CreateDefaultSubobject<UWidgetComponent>("NameWidget");
	NameWidget->SetupAttachment(GetMesh());
	HealthWidget = CreateDefaultSubobject<UWidgetComponent>("HealthWidget");
	HealthWidget->SetupAttachment(GetMesh());

	Battle = CreateDefaultSubobject<UC_BattleComponent>("Battle");
	Montages = CreateDefaultSubobject<UC_AnimComponent>("Motages");
	State = CreateDefaultSubobject<UC_StateComponent>("State");

	ConstructorHelpers::FObjectFinder<USkeletalMesh>playerMesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Ragged0.SK_CharM_Ragged0'"));
	if (playerMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(playerMesh.Object);

	ConstructorHelpers::FClassFinder<UP_AnimInstance>abpClass(TEXT("AnimBlueprint'/Game/Enemies/ABP_Enemy.ABP_Enemy_C'"));
	if (abpClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(abpClass.Class);

	TSubclassOf<UC_UserWidget_Name> nameWidgetClass;
	ConstructorHelpers::FClassFinder<UC_UserWidget_Name> nameWidget(TEXT("WidgetBlueprint'/Game/Widget/WB_Name.WB_Name_C'"));
	if (nameWidget.Succeeded())
		nameWidgetClass = nameWidget.Class;

	TSubclassOf<UC_UserWidget_Health> healthWidgetClass;
	ConstructorHelpers::FClassFinder<UC_UserWidget_Health> healthWidget(TEXT("WidgetBlueprint'/Game/Widget/WB_Health.WB_Health_C'"));
	if (healthWidget.Succeeded())
		healthWidgetClass = healthWidget.Class;

	HealthWidget->SetWidgetClass(healthWidgetClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::World);

	//NameWidget->SetWidgetClass(nameWidgetClass);
	//NameWidget->SetRelativeLocation(FVector(0,0,240));
	//NameWidget->SetDrawSize(FVector2D(240,30));
	//NameWidget->SetWidgetSpace(EWidgetSpace::Screen);


	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);

}

void AC_Enemy::BeginPlay()
{

	UMaterialInstanceConstant* mat = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/InfinityBladeWarriors/Character/CompleteCharacters/Textures_Materials/CharM_Ragged/M_Char_Ragged_Inst.M_Char_Ragged_Inst'")));
	DynamicMat = UMaterialInstanceDynamic::Create(mat, nullptr);
	GetMesh()->SetMaterial(0, DynamicMat);

	//State Change Event
	State->OnStateChanged.AddDynamic(this, &AC_Enemy::OnStateChanged);

	Super::BeginPlay();
	
	//NameWidget->InitWidget();
	//UC_UserWidget_Name* nameWidgetObject = Cast<UC_UserWidget_Name>(NameWidget->GetUserWidgetObject());
	//if (!!nameWidgetObject)
	//{
	//	nameWidgetObject->SetName(GetName());
	//}

	HealthWidget->InitWidget();
	UC_UserWidget_Health* healthWidgetObject = Cast<UC_UserWidget_Health>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidgetObject)
	{
		healthWidgetObject->Update(State->GetHealth(),State->GetMaxHealth());
	}

	Battle->SetUnarmedMode();


}

float AC_Enemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Causer = DamageCauser;
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	//Print Damage
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::SanitizeFloat(Damage));


	State->DecreaseHealth(DamageValue);
	if (State->GetHealth() <= 0.f)
	{
		State->SetDeadState();
		return DamageValue;
	}

	State->SetHitState();

	return DamageValue;
}

void AC_Enemy::OnStateChanged(ECurrentState InprevState, ECurrentState InState)
{
	switch (InState)
	{
	case ECurrentState::Hit:	 Hit();		break;
	case ECurrentState::Dead:	 Dead();	break;
	}
}

void AC_Enemy::ChangeColor(FLinearColor InColor)
{
	if (State->IsStateHit())
	{
		DynamicMat->SetVectorParameterValue("HitColor", InColor);
	}

}

void AC_Enemy::Hit()
{
	UC_UserWidget_Health* healthWidgetObject = Cast<UC_UserWidget_Health>(HealthWidget->GetUserWidgetObject());
	if(!!healthWidgetObject)
		healthWidgetObject->Update(State->GetHealth(), State->GetMaxHealth());

	Montages->PlayHit();

	//Hit stun
	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = start - target;
	direction.Normalize();
	LaunchCharacter(direction* LaunchValue,true,false);

	ChangeColor(FLinearColor::Red);
	UKismetSystemLibrary::K2_SetTimer(this,"ResetColor",0.3f,false);
}

void AC_Enemy::Dead()
{
	if (State->IsStateDead() == false) return;

	NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

	Battle->Dead();

	//Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->GlobalAnimRateScale = 0.f;
	GetMesh()->bPauseAnims = true;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = start - target;
	direction.Normalize();
	GetMesh()->AddForce(direction * DamageValue* ForceValue);
	
	UKismetSystemLibrary::K2_SetTimer(this,"End_Dead", 5.f,false);
	
} 

void AC_Enemy::End_Dead()
{
	Battle->End_Dead();

	Destroy();
}

void AC_Enemy::ResetColor()
{
	DynamicMat->SetVectorParameterValue("HitColor", FLinearColor(0, 0, 0, 0));
}




