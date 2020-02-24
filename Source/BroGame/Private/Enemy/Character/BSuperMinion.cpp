// Fill out your copyright notice in the Description page of Project Settings.


#include "BSuperMinion.h"

ABSuperMinion::ABSuperMinion()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, DeafultMeshZLocation), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleRadius(DefaultCpasuleRadius);
}

void ABSuperMinion::SetSize(float NewSize)
{
	GetCapsuleComponent()->SetCapsuleRadius(DefaultCpasuleRadius * NewSize);
	GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight * NewSize);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, DeafultMeshZLocation*NewSize));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f) * NewSize);
}
