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

	SetAttackMode(AttackMode::Default);
	EndComboState();

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	
	bFocus = false;
	PressKey = Pressed::Press_None;
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
		SetAttackMode(AttackMode::Boss);
	});

	BGameStateBase->OnIsBossDead.AddLambda([this]() -> void {
		GetWorld()->GetTimerManager().SetTimer(BackToDefaultAttackModeHandle, FTimerDelegate::CreateLambda([this]() -> void {
			SetAttackMode(AttackMode::Default);
		}), BackToDefaultAttackModeTimer, false);
	});
}

// Called every frame
void ABPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���Ͱ� �ٶ󺸴� ���� Yaw��
	YawOfLookingDirection = GetCapsuleComponent()->GetRelativeTransform().Rotator().Yaw;

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
		case AttackMode::Boss:
		{
			// Default���� SpringArm�� ȸ������ ������� �ʰ� ��Ʈ�ѷ��� ȸ������ ������̰�, Focus��忡���� SpringArm�� ȸ������ �̿��Ѵ�.
			// Focus���� �������� �� Focus�������� �ε巴�� ȭ���� ��ȯ��Ű�� ���� Default����� ���� ȸ������ SpringArmȸ������ �����صд�.
			SpringArm->SetRelativeRotation(GetControlRotation());
			break;
		}
		case AttackMode::Focus:
		{
			// ī�޶��� �������� ĳ���͸� �ε巴�� ȸ��
			GetCapsuleComponent()->SetRelativeRotation(FMath::RInterpTo(GetActorRotation(), FRotator(0.0f, GetControlRotation().Yaw, 0.0f), DeltaTime, /*IterpSpeed =*/20.0f));

			// �� Default���� �����ص� ȸ�������� Focus�������� ȭ���� �ε巴�� ��ȯ
			SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeTransform().Rotator(), FocusingRotation, DeltaTime, 5.0f));
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

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABPlayer::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABPlayer::MoveRightLeft);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABPlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ABPlayer::Attack);
	PlayerInputComponent->BindAction(TEXT("test"), EInputEvent::IE_Pressed, this, &ABPlayer::test);
	PlayerInputComponent->BindAction("Focus", EInputEvent::IE_Pressed, this, &ABPlayer::OnFocus);
	PlayerInputComponent->BindAction("Focus", EInputEvent::IE_Released, this, &ABPlayer::OffFocus);
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

Pressed ABPlayer::GetPressed() const
{
	return PressKey;
}

bool ABPlayer::IsFocusing() const
{
	return bFocus;
}

void ABPlayer::SetAttackMode(AttackMode NewAttackMode)
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
		GetController()->SetControlRotation(FRotator(-30.0f, YawOfLookingDirection, 0.0f));
		break;
	case AttackMode::Focus:
		ArmLengthTo = 450.0f;
		bUseControllerRotationYaw = true;
		//SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = false;
		SpringArm->bDoCollisionTest = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		break;
	}


}

void ABPlayer::MoveUpDown(float AxisValue)
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
	case AttackMode::Focus:

		SetForwardBackwardPressedByValue(AxisValue);

		if (!bIsAttacking)
		{
			AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), AxisValue);
		}
		break;
	}
}

void ABPlayer::MoveRightLeft(float AxisValue)
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
	case AttackMode::Focus:

		SetLeftRightPressedByValue(AxisValue);

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
	case AttackMode::Focus: 
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

void ABPlayer::SetForwardBackwardPressedByValue(float AxisValue)
{
	if (AxisValue == 0)
	{
		PressKey = Pressed::Press_None;
	}
	else if (AxisValue > 0)
	{
		PressKey = Pressed::Press_Up;
	}
	else if (AxisValue < 0)
	{
		PressKey = Pressed::Press_Down;
	}
}

void ABPlayer::SetLeftRightPressedByValue(float AxisValue)
{
	if (AxisValue > 0)
	{
		PressKey = Pressed::Press_Right;
	}
	else if (AxisValue < 0)
	{
		PressKey = Pressed::Press_Left;
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
		GetController()->SetControlRotation(FRotator(-30.0f, YawOfLookingDirection, 0.0f));
		break;
	case AttackMode::Focus:
		ArmLengthTo = 450.0f;
		//bUseControllerRotationYaw = false;
		bUseControllerRotationYaw = true;
		//SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = false;
		SpringArm->bDoCollisionTest = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
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

void ABPlayer::OnFocus()
{
	if (bIsAttacking || CurrentAttackMode == AttackMode::Default)
	{
		return;
	}

	bFocus = true;
	SetAttackMode(AttackMode::Focus);
}

void ABPlayer::OffFocus()
{
	if (CurrentAttackMode == AttackMode::Default || CurrentAttackMode == AttackMode::Boss)
	{
		return;
	}

	bFocus = false;
	SetAttackMode(AttackMode::Boss);
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
