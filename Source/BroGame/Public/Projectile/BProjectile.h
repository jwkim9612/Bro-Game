// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Actor.h"
#include "BProjectile.generated.h"

UCLASS()
class BROGAME_API ABProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// 발사체의 속도를 발사 방향으로 초기화시킨다.
	void FireInDirection(const FVector& ShootDirection);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;
};
