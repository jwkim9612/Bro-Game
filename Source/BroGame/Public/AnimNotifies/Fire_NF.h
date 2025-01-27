// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Fire_NF.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UFire_NF : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class ABProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	FName SocketName;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	int32 Count;

	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (UIMax = 90.0f, UIMin = 0.0f))
	float Angle;
};
