// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "StopAndStartAI_NS.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UStopAndStartAI_NS : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

private:
	UPROPERTY()
	class ABEnemyBase* BEnemy;

	UPROPERTY()
	class ABAIControllerBase* BAIController;
};
