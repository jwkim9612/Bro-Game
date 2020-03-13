// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Skill_NF.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API USkill_NF : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* Particle;

	// Location offset from the socket
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FVector LocationOffset;

	// Rotation offset from socket
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FRotator RotationOffset;

	// Scale to spawn the particle system at
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FVector Scale;

	// SocketName to attach to
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FName SocketName;

	UPROPERTY(EditAnywhere, Category = "Particle")
	float Radius;

	UPROPERTY()
	class UBGameInstance* BGameInstance;

	UPROPERTY()
	ACharacter* ControllingCharacter;
};
