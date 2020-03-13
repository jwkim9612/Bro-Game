// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_NF.h"
#include "BEnemyBase.h"
#include "BPlayer.h"
#include "DrawDebugHelpers.h"

void USkill_NF::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UWorld* World = MeshComp->GetWorld();
	BCHECK(World != nullptr);

	AActor* Actor = MeshComp->GetOwner();
	BCHECK(Actor != nullptr);

	const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(MeshTransform.TransformPosition(LocationOffset));
	SpawnTransform.SetRotation(MeshTransform.GetRotation() * FQuat(RotationOffset));
	SpawnTransform.SetScale3D(Scale);

	// ��ƼŬ ����
	UGameplayStatics::SpawnEmitterAtLocation(World, Particle, SpawnTransform);

	ECollisionChannel TraceChannel;

	if (Actor->IsA<ABEnemyBase>())
	{
		TraceChannel = ECollisionChannel::ECC_GameTraceChannel6;
	}
	else if (Actor->IsA<ABPlayer>())
	{
		TraceChannel = ECollisionChannel::ECC_GameTraceChannel3;
	}
	else
	{
		BLOG(Warning, TEXT("Nothing"));
		return;
	}

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Param(NAME_None, false, Actor);
	FCollisionShape DamagedSphere = FCollisionShape::MakeSphere(Radius);

	// SweepMultiByChannel���� ���۰� �������� ������ false�� ���ϵǹǷ� FVector(0.1, 0, 0)�� ����
	FVector StartLocation = SpawnTransform.GetLocation();
	FVector EndLocation = SpawnTransform.GetLocation() + FVector(0.1, 0, 0);

	DrawDebugSphere(World, SpawnTransform.GetLocation(), DamagedSphere.GetSphereRadius(), 50, FColor::Purple, true);

	bool bResult = World->SweepMultiByChannel(
		HitResults,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		TraceChannel,
		DamagedSphere,
		Param
	);

	if (bResult)
	{
		for (auto& HitResult : HitResults)
		{
			BLOG(Warning, TEXT("Hit!"));
		}
	}
}
