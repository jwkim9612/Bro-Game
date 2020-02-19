// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonster.h"
#include "BMonsterAnimInstance.h"
#include "BAIController.h"
#include "BMonsterStatComponent.h"
#include "BGameStateBase.h"
#include "BMonsterHPWidget.h"
#include "Components/WidgetComponent.h"
#include "COmponents/BoxComponent.h"

ABMonster::ABMonster()
{
	PrimaryActorTick.bCanEverTick = false;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	// AI가 부드럽게 회전하려면 Use Controller Rotation(Pawn 카테고리) 을 언체크하고 
	// Orient Rotation to Movement(Character Movement 카테고리) 를 체크한다.
	// 원리는 컨트롤러의 회전값이 아닌 캐릭터 이동 방향의 회전값을 기준으로 부드러운 회전을 하도록 하기때문
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	CurrentStat = CreateDefaultSubobject<UBMonsterStatComponent>(TEXT("MonsterStat"));
	
	///////////////// 체력 바 //////////////////////
	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
	HPWidget->SetupAttachment(GetMesh());
	HPWidget->SetRelativeLocation(FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2));
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget>
		HPWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Monster/HP.HP_C'"));

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
	
	HPWidget->SetVisibility(false);

	BAIController = Cast<ABAIController>(GetController());
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	UBMonsterHPWidget* BMonsterHPWidget = Cast<UBMonsterHPWidget>(HPWidget->GetUserWidgetObject());
	if (BMonsterHPWidget != nullptr)
	{
		BMonsterHPWidget->BindMonsterState(CurrentStat);
	}
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

	CurrentStat->SetHPToDamage(Damage);

	if (bIsDead)
	{
		BGameStateBase->SubMonsterNum();
		// 원래는 플레이어 컨트롤러 생성 후 MonsterKill 함수를 불러와 경험치를 얻음.

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
	if (!IsAttacking)
	{
		IsAttacking = true;
		BMonsterAnimInstance->PlayAttackMontage();
	}
}

void ABMonster::AttackCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Param(NAME_None, false, this);

	// 공격 시작위치벡터는 액터의 위치백터 + ( 액터의 forward벡터 * ( 엑터의 캡슐크기 / 2 ) );
	const FVector AttackStartLocation = GetActorLocation() + GetActorForwardVector() * (GetCapsuleComponent()->GetScaledCapsuleRadius() / 2);
	const FVector AttackEndLocation = GetActorLocation() + GetActorForwardVector() * ((GetCapsuleComponent()->GetScaledCapsuleRadius() / 2) + AttackRange);

	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		AttackStartLocation,
		AttackEndLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(GetCapsuleComponent()->GetScaledCapsuleRadius()),
		Param
	);

	if (bResult)
	{
		for (auto& HitResult : HitResults)
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CurrentStat->GetDamage(), DamageEvent, GetController(), this);
		}
	}
}

float ABMonster::GetMaxHP() const
{
	return MaxHP;
}

float ABMonster::GetDamage() const
{
	return Damage;
}

float ABMonster::GetAttackRange() const
{
	return AttackRange;
}

void ABMonster::Dead()
{
	bIsDead = true;
	BMonsterAnimInstance->SetIsDead(true);
	BAIController->StopAI();
	SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(DeadTimerhandle, FTimerDelegate::CreateLambda([this]() -> void {
		Destroy();
	}), DeadTimer, false);
}

void ABMonster::OnAttackMontageEnded(UAnimMontage * AnimMontage, bool Interrupted)
{
	if (!IsAttacking)
	{
		return;
	}

	IsAttacking = false;
	OnAttackEnd.Broadcast();
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
