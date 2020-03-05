// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SpawnMonster_NF.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API USpawnMonster_NF : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ABMonster> SpawnMonster;
};