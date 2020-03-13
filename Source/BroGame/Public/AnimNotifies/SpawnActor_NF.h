// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SpawnActor_NF.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API USpawnActor_NF : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AActor> ActorClass;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (UIMin = 1, UIMax = 8))
	int32 SpawnNum;

	// Location offset from the socket
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FVector LocationOffset;

	// Rotation offset from socket
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FRotator RotationOffset;

	// SocketName to attach to
	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FName SocketName;

	UPROPERTY()
	class UBGameInstance* BGameInstance;
	
	UPROPERTY()
	ACharacter* ControllingCharacter;


	bool bIsSkillActor = false;
};
