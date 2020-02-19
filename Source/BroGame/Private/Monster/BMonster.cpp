// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonster.h"
#include "BMonsterAnimInstance.h"
#include "BAIController.h"
#include "BMonsterStatComponent.h"
#include "BGameStateBase.h"

ABMonster::ABMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
}

void ABMonster::BeginPlay()
{
	Super::BeginPlay();
	
	BAIController = Cast<ABAIController>(GetController());
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
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

	CurrentStat->SetHPToDamage(Damage);

	if (bIsDead)
	{
		BGameStateBase->SubMonsterNum();
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
	
	// �Ʒ��� StopAI�� ������ ������ ���Ƽ� ��ü�� ���.
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	
	// �۵��ϴ°��� �� �𸣰���. �����̺�� Ʈ�� �״�� �۵��ϴ°� ����.
	BAIController->StopAI();

	SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(DeadTimerhandle, FTimerDelegate::CreateLambda([this]() -> void {
		Destroy();
	}), DeadTimer, false);
}
