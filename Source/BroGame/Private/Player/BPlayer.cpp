// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayer.h"


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
}

// Called when the game starts or when spawned
void ABPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

// Called to bind functionality to input
void ABPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABPlayer::MoveRight);
}

UTexture2D * ABPlayer::GetTexture() const
{
	return Texture;
}

FName ABPlayer::GetName() const
{
	return Name;
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
	DirectionToMove.X = AxisValue;
}

void ABPlayer::MoveRight(float AxisValue)
{
	DirectionToMove.Y = AxisValue;
}

