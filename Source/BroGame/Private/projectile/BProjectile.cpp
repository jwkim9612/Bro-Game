// Fill out your copyright notice in the Description page of Project Settings.


#include "BProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "..\..\Public\Projectile\BProjectile.h"

ABProjectile::ABProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->Bounciness = 0.3f;
}

void ABProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABProjectile::OnProjectileOverlapBegin);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABProjectile::OnHit);
}

void ABProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 발사체가 떨어지지않게.
	ProjectileMovementComponent->Velocity.Z = 0.0f;
}

void ABProjectile::FireInDirection(const FVector & ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABProjectile::SetContoller(AController * AIController)
{
	ProjectileInstingator = AIController;
	BCHECK(ProjectileInstingator != nullptr);
}

void ABProjectile::SetActor(AActor * Actor)
{
	ProjectileCauser = Actor;
	BCHECK(ProjectileCauser != nullptr);
}

//void ABProjectile::OnProjectileOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	//ACharacter* Character = Cast<ACharacter>(OtherActor);
//	//if (Character != nullptr)
//	//{
//	//	Destroy();
//	//}
//
//	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
//	{
//		BCHECK(ProjectileInstingator != nullptr);
//		BCHECK(ProjectileCauser != nullptr);
//
//		FDamageEvent DamageEvent;
//		OtherActor->TakeDamage(ProjectileDamage, DamageEvent, ProjectileInstingator, ProjectileCauser);
//		Destroy();
//	}
//}

void ABProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComponent != nullptr))
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character != nullptr)
		{
			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(ProjectileDamage, DamageEvent, ProjectileInstingator, ProjectileCauser);
		}

		Destroy();
	}
}
