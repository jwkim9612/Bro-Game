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

	// ĳ���� ���۽� 3���� ��ǥ�谡 �𸮾� 3���� ��ǥ��� �ٸ��� ������ Z������ -90�� ȸ����������Ѵ�
	// �� ������ ���� ��ġ�� �ٸ��� ������ Z������ ���� ���̸�ŭ ������� �Ѵ�.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	DefaultCanCombo = 1;

	SetControlMode();
	EndComboState();
}

// Called when the game starts or when spawned
void ABPlayer::BeginPlay()
{
	Super::BeginPlay();

	BPlayerState = Cast<ABPlayerState>(GetController()->PlayerState);
	BCHECK(BPlayerState != nullptr);
	
	BPlayerController = Cast<ABPlayerController>(GetController());
	BCHECK(BPlayerController);
	BPlayerController->GetHUDWidget()->UpdatePlayerHPWidget();

	AddAttackCollision();
}

// Called every frame
void ABPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ����.
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
}

float ABPlayer::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	PlayParticle(HitParticle);
	BPlayerState->SetHPToDamage(FMath::Clamp<int32>(Damage - BPlayerState->GetCurrentDefense(), 1, Damage));

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

int32 ABPlayer::GetDefaultDefense() const
{
	return DefaultDefense;
}

float ABPlayer::GetDefaultMaxHP() const
{
	return DefaultMaxHP;
}

int32 ABPlayer::GetDefaultCanCombo() const
{
	return DefaultCanCombo;
}

int32 ABPlayer::GetMaxCombo() const
{
	return MaxCombo;
}

void ABPlayer::SetIsHitting(bool IsHitting)
{
	bIsHitting = IsHitting;

	if (!IsHitting)
	{
		bIsDamageToOtherActor = false;
	}
}

void ABPlayer::SetControlMode()
{
	SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 1500.0f;
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
			// MaxCombo�� ���� ���� MaxCombo���� ���� ������ ��� �������� �޺��� ������ ������ �ɾ����
			if (CurrentCombo != BPlayerState->GetCurrentCanCombo())
			{
				OnComboInput = true;
			}
		}
	}
}

//void ABPlayer::AttackCheck()
//{
//	TArray<FHitResult> HitResults;
//	FCollisionQueryParams Param(NAME_None, false, this);
//
//	float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
//	float HitRange = 0.0f;
//	float HitDamage = 0.0f;
//	float HitScale = 0.0f;
//
//	HitRange = 100.0f;
//	//HitDamage = 10.0f;
//	HitDamage = BPlayerState->GetCurrentAttack();
//	HitScale = 70.0f;
//
//
//	bool bResult = GetWorld()->SweepMultiByChannel(
//		HitResults,
//		GetActorLocation() + GetActorForwardVector() * CapsuleRadius * 2,
//		GetActorLocation() + GetActorForwardVector() * HitRange,
//		FQuat::Identity,
//		ECollisionChannel::ECC_GameTraceChannel3,
//		FCollisionShape::MakeSphere(HitScale),
//		Param
//	);
//
//	//if (bResult)
//	//{
//	//	for (auto& HitResult : HitResults)
//	//	{
//	//		FDamageEvent DamageEvent;
//	//		HitResult.Actor->TakeDamage(HitDamage, DamageEvent, GetController(), this);
//	//	}
//	//}
//}

void ABPlayer::StartComboState()
{
	BCHECK(MaxCombo != 0);

	int32 CurrentCanCombo = BPlayerState->GetCurrentCanCombo();
	BCHECK(CurrentCanCombo != 0);

	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, CurrentCanCombo);
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

void ABPlayer::OnAttackOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (bIsHitting && !bIsDamageToOtherActor)
		{
			FDamageEvent DamageEvent;
			OtherActor->TakeDamage(BPlayerState->GetCurrentAttack(), DamageEvent, GetController(), this);
			bIsDamageToOtherActor = true;
		}
	}
}

void ABPlayer::AddAttackCollision()
{
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	UCapsuleComponent* CapsuleCollision;
	for (auto& Component : Components)
	{
		CapsuleCollision = Cast<UCapsuleComponent>(Component);

		if (CapsuleCollision == RootComponent)
		{
			continue;
		}

		if (CapsuleCollision != nullptr)
		{
			AttackCollisions.Add(CapsuleCollision);
			CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ABPlayer::OnAttackOverlapBegin);
		}
	}
}
