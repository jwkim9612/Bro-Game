// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Actor.h"
#include "BSkillActor.generated.h"

UCLASS()
class BROGAME_API ABSkillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABSkillActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetController(AController* Controller);
	void SetActor(AActor* Actor);

private:
	UFUNCTION()
	void OnSkillOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnParticleDone(UParticleSystemComponent* ParticleSystem);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Collision")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 Damage;

	FTimerHandle DoneTimerHandle;
	float DoneTimer;

	UPROPERTY()
	AController* CauserController;

	UPROPERTY()
	AActor* CauserActor;
};
