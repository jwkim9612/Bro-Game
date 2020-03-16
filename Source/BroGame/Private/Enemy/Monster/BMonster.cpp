// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonster.h"
#include "BMonsterAnimInstance.h"
#include "BMonsterAIController.h"
#include "BEnemyStatComponent.h"
#include "BGameStateBase.h"
#include "BMonsterHPWidget.h"
#include "BPlayerController.h"
#include "BGamePauseWidget.h"
#include "BHUDWidget.h"
#include "Components/WidgetComponent.h"
#include "COmponents/BoxComponent.h"

ABMonster::ABMonster()
{
	PrimaryActorTick.bCanEverTick = false;



	///////////////// 체력 바 //////////////////////
	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
	HPWidget->SetupAttachment(GetMesh());
	HPWidget->SetRelativeLocation(FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2));
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget>
		HPWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Monster/HP_Monster.HP_Monster_C'"));

	if (HPWidgetClass.Succeeded())
	{
		HPWidget->SetWidgetClass(HPWidgetClass.Class);
		HPWidget->SetDrawSize(FVector2D(50.0f, 5.0f));
	}

	//HPWidget->SetVisibility(false); 왜 안먹히지.
	///////////////////////////////////////////////

	VisibleHPBox = CreateDefaultSubobject<UBoxComponent>(TEXT("VisibleHPBox"));
	VisibleHPBox->SetupAttachment(GetMesh());
	VisibleHPBox->SetCollisionProfileName(TEXT("VisibleHPBar"));
	VisibleHPBox->SetBoxExtent(VisibleHPBarBoxSize);
	VisibleHPBox->OnComponentBeginOverlap.AddDynamic(this, &ABMonster::OnVisibleHPBarBoxBeginOverlap);
	VisibleHPBox->OnComponentEndOverlap.AddDynamic(this, &ABMonster::OnVisibleHPBarBoxEndOverlap);
}

void ABMonster::BeginPlay()
{
	Super::BeginPlay();
	BAIController = Cast<ABMonsterAIController>(GetController());

	HPWidget->SetVisibility(false);

	UBMonsterHPWidget* BMonsterHPWidget = Cast<UBMonsterHPWidget>(HPWidget->GetUserWidgetObject());
	if (BMonsterHPWidget != nullptr)
	{
		BMonsterHPWidget->BindMonsterState(CurrentStat);
	}

	BGameStateBase->OnIsBossDead.AddUObject(this, &ABMonster::Dead);
}

void ABMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BMonsterAnimInstance = Cast<UBMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	BCHECK(BMonsterAnimInstance != nullptr);
	
	BMonsterAnimInstance->OnMontageEnded.AddDynamic(this, &ABMonster::OnAttackMontageEnded);
	BMonsterAnimInstance->OnHitAttack.AddUObject(this, &ABMonster::AttackCheck);
	CurrentStat->OnHPIsZero.AddUObject(this, &ABMonster::Dead);
}

float ABMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (bIsDead)
	{
		ABPlayerController* InstigatorController = Cast<ABPlayerController>(EventInstigator);
		if (InstigatorController != nullptr)
		{
			InstigatorController->MonsterKill(this);
		}

		return FinalDamage;
	}

	BMonsterAnimInstance->PlayHitMontage();

	return FinalDamage;
}

void ABMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABMonster::Attack()
{
	if (!IsAttacking())
	{
		bIsAttacking = true;
		BMonsterAnimInstance->PlayAttackMontage();
	}
}

void ABMonster::SetSize(float NewSize)
{
	if (NewSize == 0.0f)
	{
		return;
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight * NewSize);
	GetCapsuleComponent()->SetCapsuleRadius(DefaultCapsuleRadius * NewSize);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, DefaultMeshZLocation*NewSize));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f) * NewSize);
}

void ABMonster::SetDefaultStat(FBMonsterInfo BMonsterInfo)
{
	SetDamage(BMonsterInfo.DefaultDamage);
	SetMaxHP(BMonsterInfo.DefaultMaxHP);
	SetAttackRange(BMonsterInfo.AttackRange);
	SetDropMoney(BMonsterInfo.DefaultDropMoney);
	
	DefaultCapsuleHalfHeight = BMonsterInfo.CapsuleHalfHeight;
	DefaultCapsuleRadius = BMonsterInfo.CapsuleRadius;
	DefaultMeshZLocation = BMonsterInfo.MeshZLocation;

	GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleRadius(DefaultCapsuleRadius);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, DefaultMeshZLocation));
}

void ABMonster::Dead()
{
	Super::Dead();

//	BGameStateBase->SubMonsterNum();
	BMonsterAnimInstance->SetIsDead(true);
	BPlayerController->GetGamePauseWidget()->FOnMainMenuClicked.AddLambda([this]() -> void {
		GetWorld()->GetTimerManager().ClearTimer(DeadTimerHandle);
	});

	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		Destroy();
	}), DeadTimer, false);
}

void ABMonster::OnVisibleHPBarBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		HPWidget->SetVisibility(true);
	}
}

void ABMonster::OnVisibleHPBarBoxEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		HPWidget->SetVisibility(false);
	}
}
