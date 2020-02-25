// Fill out your copyright notice in the Description page of Project Settings.


#include "BBoss.h"
#include "BBossAIController.h"

void ABBoss::BeginPlay()
{
	Super::BeginPlay();

	BAIController = Cast<ABBossAIController>(GetController());
}

FName ABBoss::GetBossName() const
{
	return BossName;
}

UTexture2D* ABBoss::GetWantedPhoto() const
{
	return WantedPhoto;
}
