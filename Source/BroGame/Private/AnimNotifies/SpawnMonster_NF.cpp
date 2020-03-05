// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnMonster_NF.h"
#include "BBoss.h"
#include "BMonster.h"

void USpawnMonster_NF::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABBoss* BBoss = Cast<ABBoss>(MeshComp->GetOwner());
	BCHECK(BBoss != nullptr);
	
	ABMonster* BMonster = SpawnMonster->GetDefaultObject<ABMonster>();
	BCHECK(BMonster != nullptr);

	FVector vec = BBoss->GetActorLocation();
	FRotator rot = FRotator::ZeroRotator;

	UWorld* World = BBoss->GetWorld();
	BCHECK(World != nullptr);

	for (int32 i = 0; i < 8; ++i)
	{
		World->SpawnActor<ABMonster>(BMonster->GetClass(), vec, rot);
	}
}