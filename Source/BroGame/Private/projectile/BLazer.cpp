// Fill out your copyright notice in the Description page of Project Settings.


#include "BLazer.h"

ABLazer::ABLazer()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	RootComponent = SceneComponent;
	
	CollisionComponent->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(RootComponent);

	CollisionComponent->SetCollisionProfileName(TEXT("Lazer"));
}

void ABLazer::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABLazer::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABLazer::OnLazerOverlapBegin);
	ParticleComponent->OnSystemFinished.AddDynamic(this, &ABLazer::OnParticleFinished);
}

void ABLazer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABLazer::SetContoller(AController * AIController)
{
	LazerInstingator = AIController;
	BCHECK(LazerInstingator != nullptr);
}

void ABLazer::SetActor(AActor * Actor)
{
	LazerCauser = Actor;
	BCHECK(LazerCauser != nullptr);
}

void ABLazer::OnLazerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp!= nullptr))
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character != nullptr)
		{
			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(LazerDamage, DamageEvent, LazerInstingator, LazerCauser);
		}
	}
}

void ABLazer::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	BLOG(Warning, TEXT("Hit!"));

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComponent != nullptr))
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character != nullptr)
		{
			BLOG(Warning, TEXT("Hit Character!"));
		
		}
	}
}

void ABLazer::OnParticleFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}
