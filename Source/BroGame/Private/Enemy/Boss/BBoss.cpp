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

	//BAIController = Cast<ABBossAIController>(GetController());
	BAIController = Cast<ABBossAIController>(GetController());
	//BPlayerController->GetHUDWidget()->OnStartCinematic.AddLambda([this]() -> void {
	//	BAIController->StopAI();
	//});

	//BPlayerController->GetHUDWidget()->OnEndCinematic.AddLambda([this]() -> void {
	//	BAIController->RunAI();
	//});

	if (bIsForCinema)
	{
		return;
	}

	BPlayerController->GetHUDWidget()->BindBossHPWidget(this);
}

void ABBoss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BBossAnimInstance = Cast<UBBossAnimInstance>(GetMesh()->GetAnimInstance());
	BCHECK(BBossAnimInstance != nullptr);

	CurrentStat->OnHPIsZero.AddUObject(this, &ABBoss::Dead);
}

float ABBoss::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), FRotator::ZeroRotator, true);

	if (bIsDead)
	{
		BGameStateBase->SetIsBossDead(true);
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

void ABBoss::Dead()
{
	Super::Dead();

	BBossAnimInstance->SetIsDead(true);
	BPlayerController->GetGamePauseWidget()->FOnMainMenuClicked.AddLambda([this]() -> void {
		GetWorld()->GetTimerManager().ClearTimer(DeadTimerhandle);
	});

	GetWorld()->GetTimerManager().SetTimer(DeadTimerhandle, FTimerDelegate::CreateLambda([this]() -> void {
		Destroy();
	}), DeadTimer, false);
}
