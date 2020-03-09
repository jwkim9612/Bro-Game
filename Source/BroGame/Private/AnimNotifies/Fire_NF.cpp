// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire_NF.h"
#include "BBoss.h"
#include "BProjectile.h"

void UFire_NF::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABBoss* BBoss = Cast<ABBoss>(MeshComp->GetOwner());
	BCHECK(BBoss != nullptr);

	FVector Vec;
	FRotator Rot;

	Vec = MeshComp->GetSocketLocation(SocketName);
	Rot = BBoss->GetActorForwardVector().Rotation();

	UWorld* World = BBoss->GetWorld();
	if (World)
	{
		BLOG(Warning, TEXT("InWorld"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = BBoss;
		SpawnParams.Instigator = BBoss->Instigator;

		ABProjectile* Projectile = World->SpawnActor<ABProjectile>(ProjectileClass, Vec, Rot, SpawnParams);
		if (Projectile)
		{
			BLOG(Warning, TEXT("Spawn Good"));
			FVector LaunchDirection = Rot.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}

	}
}
