// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayer.h"
#include "BPlayerAnimInstance.h"
#include "BPlayerController.h"
#include "BPlayerState.h"
#include "BHUDWidget.h"

// Sets default values
ABPlayer::ABPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 제작시 3차원 좌표계가 언리얼 3차원 좌표계와 다르기 때문에 Z축으로 -90도 회전시켜줘야한다
	// 또 액터의 기준 위치가 다르기 때문에 Z축으로 절반 높이만큼 내려줘야 한다.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	SetControlMode();
	EndComboState();
}

// Called when the game starts or when spawned
void ABPlayer::BeginPlay()
{
	Super::BeginPlay();

	BPlayerState = Cast<ABPlayerState>(GetController()->PlayerState);
	BCHECK(BPlayerState != nullptr);
	BPlayerState->InitPlayerData();
	
	ABPlayerController* BPlayerController = Cast<ABPlayerController>(GetController());
	BCHECK(BPlayerController);
	BPlayerController->GetHUDWidget()->UpdateHPWidget();
}

// Called every frame
void ABPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 이유 적기.
	if (DirectionToMove.SizeSquared() > 0.0f)
	{
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove);
	}
}

void ABPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BAnimInstance = Cast<UBPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	BCHECK(BAnimInstance != nullptr);

	BAnimInstance->OnMontageEnded.AddDynamic(this, &ABPlayer::OnAttackMontageEnded);
	BAnimInstance->OnCanNextAttack.AddLambda([this]()-> void {

		if (OnComboInput)
		{
			OnComboInput = false;
			StartComboState();
			BAnimInstance->JumptoNextAttackSection(CurrentCombo);
		}
	});

	BAnimInstance->OnHitAttack.AddUObject(this, &ABPlayer::AttackCheck);
}

float ABPlayer::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	PlayParticle(HitParticle);
	BPlayerState->SetHPToDamage(Damage);

	return FinalDamage;
}

// Called to bind functionality to input
void ABPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABPlayer::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ABPlayer::Attack);
}

UTexture2D * ABPlayer::GetTexture() const
{
	return Texture;
}

FName ABPlayer::GetName() const
{
	return Name;
}

int32 ABPlayer::GetDefaultAttack() const
{
	return DefaultAttack;
}

float ABPlayer::GetDefaultMaxHP() const
{
	return DefaultMaxHP;
}

void ABPlayer::SetControlMode()
{
	SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 1200.0f;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void ABPlayer::MoveForward(float AxisValue)
{
	if (bIsAttacking)
	{
		DirectionToMove.X = 0;
	}
	else
	{
		DirectionToMove.X = AxisValue;
	}
}

void ABPlayer::MoveRight(float AxisValue)
{
	if (bIsAttacking)
	{
		DirectionToMove.Y = 0;
	}
	else
	{
		DirectionToMove.Y = AxisValue;
	}
}

void ABPlayer::Attack()
{
	if (!bIsAttacking)
	{
		bIsAttacking = true;
		StartComboState();
	
		BAnimInstance->PlayGroundAttackMontage();
	}
	else
	{
		if (CanNextAttack)
		{
			// MaxCombo를 가장 높은 MaxCombo보다 적게 설정한 경우 무한으로 콤보를 때리기 때문에 걸어놓음
			if (CurrentCombo != MaxCombo)
			{
				OnComboInput = true;
			}
		}
	}
}

void ABPlayer::AttackCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Param(NAME_None, false, this);

	float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	float HitRange = 0.0f;
	float HitDamage = 0.0f;
	float HitScale = 0.0f;

	HitRange = 100.0f;
	HitDamage = 10.0f;
	//HitDamage = WPlayerState->GetAttack();
	HitScale = 70.0f;


	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		GetActorLocation() + GetActorForwardVector() * CapsuleRadius * 2,
		GetActorLocation() + GetActorForwardVector() * HitRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(HitScale),
		Param
	);

	if (bResult)
	{
		for (auto& HitResult : HitResults)
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(HitDamage, DamageEvent, GetController(), this);
		}
	}
}

void ABPlayer::StartComboState()
{
	BCHECK(MaxCombo != 0);
	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, MaxCombo);
	CanNextAttack = true;
}

void ABPlayer::EndComboState()
{
	OnComboInput = false;
	CanNextAttack = false;
	CurrentCombo = 0;
}

void ABPlayer::PlayParticle(UParticleSystem * ParticleSystem) const
{
	BCHECK(ParticleSystem != nullptr);
	UGameplayStatics::SpawnEmitterAttached(ParticleSystem, RootComponent, NAME_None);
}

void ABPlayer::OnAttackMontageEnded(UAnimMontage * AnimMontage, bool Interrupted)
{
	if (!bIsAttacking)
	{
		return;
	}

	bIsAttacking = false;
	EndComboState();
}

