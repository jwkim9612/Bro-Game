// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire_NF.h"
#include "BBoss.h"
#include "BProjectile.h"

void UFire_NF::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACharacter* ControllingPawn = Cast<ACharacter>(MeshComp->GetOwner());
	BCHECK(ControllingPawn != nullptr);

	FVector SpawnVector;
	FRotator SpawnRotator;

	SpawnVector = MeshComp->GetSocketLocation(SocketName);
	SpawnRotator = ControllingPawn->GetActorForwardVector().Rotation();

	UWorld* World = ControllingPawn->GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = ControllingPawn;
		SpawnParams.Instigator = ControllingPawn->Instigator;

		float Gap = Count > 1 ? Angle / (float)(Count - 1) : 0;
		float StartAngle = Angle / 2.0f;

		for (int32 i = 0; i < Count; ++i)
		{
			
			ABProjectile* Projectile = World->SpawnActor<ABProjectile>(ProjectileClass, SpawnVector, SpawnRotator, SpawnParams);
			if (Projectile)
			{
				FRotator FireAngle = SpawnRotator;
				FireAngle.Yaw += StartAngle - Gap * i;
				FVector LaunchDirection = FireAngle.Vector();
				// 발사체가 떨어지지않게.
				LaunchDirection.Z = 0.0f;


				Projectile->FireInDirection(LaunchDirection);
				Projectile->SetContoller(ControllingPawn->GetController());
				Projectile->SetActor(ControllingPawn);
			}
		}
	}
}
