// Fill out your copyright notice in the Description page of Project Settings.


#include "BEnemyBase.h"
#include "BMonsterAnimInstance.h"
#include "BAIControllerBase.h"
#include "BEnemyStatComponent.h"
#include "BGameStateBase.h"
#include "BPlayerController.h"

ABEnemyBase::ABEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ - 90�� ȸ����������Ѵ�
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

	CurrentStat = CreateDefaultSubobject<UBEnemyStatComponent>(TEXT("MonsterStat"));
}

void ABEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BPlayerController = Cast<ABPlayerController>(UGameplayStatics::GetGameInstance(GetWorld())->GetPrimaryPlayerController());
	
	if (bIsForCinema)
	{
		return;
	}

	BGameStateBase->AddMonsterNum();
}

void ABEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

float ABEnemyBase::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	BLOG(Warning, TEXT("TakeDamage : %f"), Damage);
	CurrentStat->SetHPToDamage(Damage);

	return FinalDamage;
}

void ABEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABEnemyBase::Attack()
{

}

void ABEnemyBase::AttackCheck()
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

float ABEnemyBase::GetMaxHP() const
{
	return MaxHP;
}

float ABEnemyBase::GetDamage() const
{
	return DefaultDamage;
}

float ABEnemyBase::GetAttackRange() const
{
	return AttackRange;
}

int32 ABEnemyBase::GetDropMoney() const
{
	return DropMoney;
}

bool ABEnemyBase::IsAttacking() const
{
	return bIsAttacking == true ? true : false;
}

void ABEnemyBase::SetDamage(float NewDamage)
{
	DefaultDamage = NewDamage;
}

void ABEnemyBase::SetMaxHP(float NewHP)
{
	MaxHP = NewHP;
}

void ABEnemyBase::SetSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void ABEnemyBase::SetDropMoney(int32 NewDropMoney)
{
	DropMoney = NewDropMoney;
}

UBEnemyStatComponent * ABEnemyBase::GetCurrentStat() const
{
	return CurrentStat;
}

void ABEnemyBase::Dead()
{
	bIsDead = true;
	BAIController->StopAI();
	SetActorEnableCollision(false);
}

void ABEnemyBase::OnAttackMontageEnded(UAnimMontage * AnimMontage, bool Interrupted)
{
	if (!IsAttacking())
	{
		return;
	}

	bIsAttacking = false;
	OnAttackEnd.Broadcast();
}

