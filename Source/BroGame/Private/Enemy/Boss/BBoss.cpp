// Fill out your copyright notice in the Description page of Project Settings.


#include "BBoss.h"
#include "BBossAIController.h"
#include "BBossAnimInstance.h"
#include "BEnemyStatComponent.h"
#include "BPlayerController.h"
#include "BGameStateBase.h"
#include "BGamePauseWidget.h"
#include "BHUDWidget.h"

void ABBoss::BeginPlay()
{
	Super::BeginPlay();

	BAIController = Cast<ABBossAIController>(GetController());
	BPlayerController->GetHUDWidget()->BindBossHPWidget(this);
}

void ABBoss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BBossAnimInstance = Cast<UBBossAnimInstance>(GetMesh()->GetAnimInstance());
	BCHECK(BBossAnimInstance != nullptr);

	BBossAnimInstance->OnMontageEnded.AddDynamic(this, &ABBoss::OnAttackMontageEnded);
	BBossAnimInstance->OnHitAttack.AddUObject(this, &ABBoss::AttackCheck);
	CurrentStat->OnHPIsZero.AddUObject(this, &ABBoss::Dead);
}

float ABBoss::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), FRotator::ZeroRotator, true);

	if (bIsDead)
	{
		//BGameStateBase->SetIsBossDead(true);
		ABPlayerController* InstigatorController = Cast<ABPlayerController>(EventInstigator);
		if (InstigatorController != nullptr)
		{
			InstigatorController->MonsterKill(this);
		}
	}

	return FinalDamage;
}

FName ABBoss::GetBossName() const
{
	return BossName;
}

UTexture2D* ABBoss::GetWantedPhoto() const
{
	return WantedPhoto;
}

UBBossAnimInstance * ABBoss::GetAnimInstance() const
{
	return BBossAnimInstance;
}

void ABBoss::SetWantedPhoto(UTexture2D * NewWantedPhoto)
{
	WantedPhoto = NewWantedPhoto;
}

void ABBoss::SetHitParticle(UParticleSystem * NewHitParticle)
{
	HitParticle = NewHitParticle;
}

void ABBoss::SetStat(FBBossInfo BossInfo)
{
	SetDamage(BossInfo.Damage);
	SetMaxHP(BossInfo.MaxHP);
	SetAttackRange(BossInfo.AttackRange);
	SetDropMoney(BossInfo.DropMoney);
	SetWantedPhoto(BossInfo.WantedPhoto);
	SetHitParticle(BossInfo.HitParticle);
}

void ABBoss::Attack()
{
	if (!IsAttacking())
	{
		bIsAttacking = true;
		BBossAnimInstance->PlayAttackMontage();
	}
}

void ABBoss::Dead()
{
	Super::Dead();

	BGameStateBase->SetIsBossDead(true);
	BBossAnimInstance->SetIsDead(true);
	BPlayerController->GetGamePauseWidget()->FOnMainMenuClicked.AddLambda([this]() -> void {
		GetWorld()->GetTimerManager().ClearTimer(DeadTimerhandle);
	});

	GetWorld()->GetTimerManager().SetTimer(DeadTimerhandle, FTimerDelegate::CreateLambda([this]() -> void {
		Destroy();
	}), DeadTimer, false);
}
