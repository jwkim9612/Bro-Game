// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire_NF.h"
#include "BBoss.h"
#include "BProjectile.h"

void UFire_NF::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACharacter* ControllingPawn = Cast<ACharacter>(MeshComp->GetOwner());
	BCHECK(ControllingPawn != nullptr);

	FVector Vec;
	FRotator Rot;

	Vec = MeshComp->GetSocketLocation(SocketName);
	Rot = ControllingPawn->GetActorForwardVector().Rotation();

	UWorld* World = ControllingPawn->GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = ControllingPawn;
		SpawnParams.Instigator = ControllingPawn->Instigator;

		ABProjectile* Projectile = World->SpawnActor<ABProjectile>(ProjectileClass, Vec, Rot, SpawnParams);
		if (Projectile)
		{
			FVector LaunchDirection = Rot.Vector();
			// 발사체가 떨어지지않게.
			LaunchDirection.Z = 0.0f;

			Projectile->FireInDirection(LaunchDirection);
			Projectile->SetContoller(ControllingPawn->GetController());
			Projectile->SetActor(ControllingPawn);
		}

	}
}
