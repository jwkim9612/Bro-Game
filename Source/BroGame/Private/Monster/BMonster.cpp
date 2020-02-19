// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonster.h"
#include "BMonsterAnimInstance.h"
#include "BAIController.h"
#include "BMonsterStatComponent.h"

ABMonster::ABMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));


	CurrentStat = CreateDefaultSubobject<UBMonsterStatComponent>(TEXT("MonsterStat"));

	DeadTimer = 3.0f;
}

void ABMonster::BeginPlay()
{
	Super::BeginPlay();
	
	BAIController = Cast<ABAIController>(GetController());

}

void ABMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BMonsterAnimInstance = Cast<UBMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	BCHECK(BMonsterAnimInstance != nullptr);

	CurrentStat->OnHPIsZero.AddUObject(this, &ABMonster::Dead);
}

float ABMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	BMonsterAnimInstance->PlayHitMontage();
	//BAIController->StopAI();

	CurrentStat->SetHPToDamage(Damage);

	if (bIsDead)
	{
		// ������ �÷��̾� ��Ʈ�ѷ� ���� �� MonsterKill �Լ��� �ҷ��� ����ġ�� ����.
	}

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

float ABMonster::GetMaxHP() const
{
	return MaxHP;
}

float ABMonster::GetAttack() const
{
	return Attack;
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

