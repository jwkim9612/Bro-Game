// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor_NF.h"
#include "BGameInstance.h"

void USpawnActor_NF::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UWorld* World = MeshComp->GetWorld();
	BCHECK(World != nullptr);

	AActor* Actor = ActorClass->GetDefaultObject<AActor>();
	BCHECK(Actor != nullptr);

	const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(MeshTransform.TransformPosition(LocationOffset));
	SpawnTransform.SetRotation(MeshTransform.GetRotation() * FQuat(RotationOffset));

	BGameInstance = Cast<UBGameInstance>(World->GetGameInstance());
	BCHECK(BGameInstance != nullptr);

	ControllingCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	BCHECK(ControllingCharacter != nullptr);

	for (int32 i = 0; i < SpawnNum; ++i)
	{
		FVector vec = BGameInstance->GetSnailLocation(ControllingCharacter->GetActorLocation(), 0, ControllingCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius() * 2, i + 1);
		SpawnTransform.SetLocation(vec);

		World->SpawnActor<AActor>(Actor->GetClass(), SpawnTransform);
	}
}
