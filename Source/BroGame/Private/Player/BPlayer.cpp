// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayer.h"
#include "BPlayerAnimInstance.h"
#include "BPlayerController.h"
#include "BPlayerState.h"
#include "BGameInstance.h"
#include "BGameStateBase.h"
#include "BLevelScriptActor.h"
#include "BHUDWidget.h"
#include "DrawDebugHelpers.h"

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

	SetControlMode(AttackMode::Default);
	EndComboState();

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
}

// Called when the game starts or when spawned
void ABPlayer::BeginPlay()
{
	Super::BeginPlay();

	BPlayerState = Cast<ABPlayerState>(GetController()->PlayerState);
	BPlayerController = Cast<ABPlayerController>(GetController());	
	BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	BCHECK(BPlayerState != nullptr);
	BCHECK(BPlayerController != nullptr);
	BCHECK(BGameInstance != nullptr);
	BCHECK(BGameStateBase != nullptr);

	BPlayerController->GetHUDWidget()->UpdatePlayerHPWidget();
	BGameInstance->GetCurrentLevelScriptActor()->OnEndCinematic.AddLambda([this]() -> void {
		SetControlMode(AttackMode::Boss);
	});

	BGameStateBase->OnIsBossDead.AddLambda([this]() -> void {
		GetWorld()->GetTimerManager().SetTimer(BackToDefaultAttackModeHandle, FTimerDelegate::CreateLambda([this]() -> void {
			SetControlMode(AttackMode::Default);
		}), BackToDefaultAttackModeTimer, false);
	});
}

// Called every frame
void ABPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentAttackMode)
	{
		case AttackMode::Default:
		{
			// ���� ����.
			if (DirectionToMove.SizeSquared() > 0.0f)
			{
				GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
				AddMovementInput(DirectionToMove);
			}
			break;
		}
	}
}

void ABPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BAnimInstance = Cast<UBPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	BCHECK(BAnimInstance != nullptr);

	BAnimInstance->OnMontageEnded.AddDynamic(this, &ABPlayer::OnAttackMontageEnded);
	BAnimInstance->OnHitAttack.AddUObject(this, &ABPlayer::AttackCheck);
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

void ABPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABPlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ABPlayer::Attack);
	PlayerInputComponent->BindAction(TEXT("test"), EInputEvent::IE_Pressed, this, &ABPlayer::test);
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

void ABPlayer::SetControlMode(AttackMode NewAttackMode)
{
	CurrentAttackMode = NewAttackMode;

	switch (NewAttackMode)
	{
	case AttackMode::Default:
		SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
		//SpringArm->TargetArmLength = 1500.0f;
		ArmLengthTo = 1300.0f;
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case AttackMode::Boss:
		ArmLengthTo = 600.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		bUseControllerRotationYaw = false;	// ���콺�� ���� ĳ���Ͱ� �����ϰ�����.
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bDoCollisionTest = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		//GetController()->SetControlRotation(FRotator(-30.0f, YawOfLookingDirection, 0.0f));
		break;
	}


}

void ABPlayer::MoveForward(float AxisValue)
{
	switch (CurrentAttackMode)
	{
	case AttackMode::Default:
		if (bIsAttacking)
		{
			DirectionToMove.X = 0;
		}
		else
		{
			DirectionToMove.X = AxisValue;
		}
		break;

	case AttackMode::Boss:
		if (!bIsAttacking)
		{
			AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), AxisValue);
		}
		break;
	}
}

void ABPlayer::MoveRight(float AxisValue)
{
	switch (CurrentAttackMode)
	{
	case AttackMode::Default:
		if (bIsAttacking)
		{
			DirectionToMove.Y = 0;
		}
		else
		{
			DirectionToMove.Y = AxisValue;
		}
		break;

	case AttackMode::Boss:
		if (!bIsAttacking)
		{
			AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), AxisValue);
		}
		break;
	}
}

void ABPlayer::Turn(float AxisValue)
{
	switch (CurrentAttackMode)
	{
	case AttackMode::Boss:
		AddControllerYawInput(AxisValue);
		break;
	}
}

void ABPlayer::LookUp(float AxisValue)
{
	switch (CurrentAttackMode)
	{
	case AttackMode::Boss:
		AddControllerPitchInput(AxisValue);
		break;
	}
}

void ABPlayer::test()
{
	if (CurrentAttackMode == AttackMode::Default)
	{
		CurrentAttackMode = AttackMode::Boss;
	}
	else
	{
		CurrentAttackMode = AttackMode::Default;
	}
	
	switch (CurrentAttackMode)
	{
	case AttackMode::Default:
		SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
		//SpringArm->TargetArmLength = 1500.0f;
		ArmLengthTo = 1300.0f;
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case AttackMode::Boss:
		ArmLengthTo = 600.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		bUseControllerRotationYaw = false;	// ���콺�� ���� ĳ���Ͱ� �����ϰ�����.
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bDoCollisionTest = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		//GetController()->SetControlRotation(FRotator(-30.0f, YawOfLookingDirection, 0.0f));
		break;
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

// ���⿡ �ݸ����� �־ �� �ݸ����� ������ �������� �ް� �Ϸ��� �ߴµ� ĳ���Ͱ� �ݸ����� �� ���� �ʾƼ�
// Sweep�Լ��� �̿��ߴ�.
void ABPlayer::AttackCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Param(NAME_None, false, this);

	float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	float HitRange = 0.0f;
	float HitDamage = 0.0f;
	float HitScale = 0.0f;

	HitRange = 100.0f;
	//HitDamage = 10.0f;
	HitDamage = BPlayerState->GetCurrentAttack();
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

	FVector TraceVec = GetActorForwardVector() * HitRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = HitRange * 0.5f + HitScale;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		HitScale,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

}

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
