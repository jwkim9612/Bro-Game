// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Actor.h"
#include "BLazer.generated.h"

UCLASS()
class BROGAME_API ABLazer : public AActor
{
	GENERATED_BODY()
	
public:	
	ABLazer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetContoller(AController* AIController);
	void SetActor(AActor* Actor);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	UFUNCTION()
	void OnLazerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnParticleFinished(UParticleSystemComponent* ParticleSystem);

private:
	UPROPERTY(VisibleAnywhere, Category = "Lazer")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Lazer")
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Lazer")
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY()
	AController* LazerInstingator;

	UPROPERTY()
	AActor* LazerCauser;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float LazerDamage;
};
