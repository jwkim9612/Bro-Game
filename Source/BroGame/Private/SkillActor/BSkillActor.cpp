// Fill out your copyright notice in the Description page of Project Settings.


#include "BSkillActor.h"
#include "Particles/ParticleModuleRequired.h"
#include "..\..\Public\SkillActor\BSkillActor.h"

ABSkillActor::ABSkillActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	
	RootComponent = CollisionComponent;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(RootComponent);
}

void ABSkillActor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABSkillActor::OnSkillOverlapBegin);

	ParticleComponent->OnSystemFinished.AddDynamic(this, &ABSkillActor::OnParticleDone);
}

void ABSkillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABSkillActor::SetController(AController * Controller)
{
	CauserController = Controller;
	BCHECK(CauserController != nullptr);
}

void ABSkillActor::SetActor(AActor * Actor)
{
	CauserActor = Actor;
	BCHECK(CauserActor != nullptr);
}

void ABSkillActor::OnSkillOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, CauserController, CauserActor);
	}
}

void ABSkillActor::OnParticleDone(UParticleSystemComponent * ParticleSystem)
{
	Destroy();
}
