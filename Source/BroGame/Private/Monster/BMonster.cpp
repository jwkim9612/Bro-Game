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

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	// AI�� �ε巴�� ȸ���Ϸ��� Use Controller Rotation(Pawn ī�װ�) �� ��üũ�ϰ� 
	// Orient Rotation to Movement(Character Movement ī�װ�) �� üũ�Ѵ�.
	// ������ ��Ʈ�ѷ��� ȸ������ �ƴ� ĳ���� �̵� ������ ȸ������ �������� �ε巯�� ȸ���� �ϵ��� �ϱ⶧��
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	CurrentStat = CreateDefaultSubobject<UBMonsterStatComponent>(TEXT("MonsterStat"));
	
	///////////////// ü�� �� //////////////////////
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

	//HPWidget->SetVisibility(false); �� �ȸ�����.
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
		// ������ �÷��̾� ��Ʈ�ѷ� ���� �� MonsterKill �Լ��� �ҷ��� ����ġ�� ����.

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

	// ���� ������ġ���ʹ� ������ ��ġ���� + ( ������ forward���� * ( ������ ĸ��ũ�� / 2 ) );
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
