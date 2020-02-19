// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterAnimInstance.h"
#include "BMonster.h"

void UBMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABMonster* Monster = Cast<ABMonster>(TryGetPawnOwner());
	if (Monster != nullptr)
	{
		CurrentSpeed = Monster->GetVelocity().Size();
	}
}

void UBMonsterAnimInstance::PlayAttackMontage()
{
	BCHECK(AttackMontage != nullptr);
	Montage_Play(AttackMontage);
}

void UBMonsterAnimInstance::PlayHitMontage()
{
	BCHECK(HitMontage != nullptr);
	Montage_Play(HitMontage);
}

void UBMonsterAnimInstance::SetIsDead(bool IsDead)
{
	bIsDead = IsDead;
}

void UBMonsterAnimInstance::AnimNotify_HitAttack()
{
	OnHitAttack.Broadcast();
}
