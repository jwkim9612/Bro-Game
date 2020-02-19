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
		// 원래는 플레이어 컨트롤러 생성 후 MonsterKill 함수를 불러와 경험치를 얻음.
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
	
	// 아래의 StopAI가 먹히지 않은것 같아서 대체로 사용.
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	
	// 작동하는건지 잘 모르겠음. 비헤이비어 트리 그대로 작동하는거 같음.
	BAIController->StopAI();

	SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(DeadTimerhandle, FTimerDelegate::CreateLambda([this]() -> void {
		Destroy();
	}), DeadTimer, false);
}
