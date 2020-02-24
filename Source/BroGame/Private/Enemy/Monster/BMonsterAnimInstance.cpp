// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterAnimInstance.h"
#include "BMonster.h"

void UBMonsterAnimInstance::PlayHitMontage()
{
	BCHECK(HitMontage != nullptr);
	Montage_Play(HitMontage);
}
