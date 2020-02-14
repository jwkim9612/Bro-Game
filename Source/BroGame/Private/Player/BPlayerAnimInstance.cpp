// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerAnimInstance.h"
#include "BPlayer.h"

void UBPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABPlayer* PlayerCharacter = Cast<ABPlayer>(TryGetPawnOwner());
	if (PlayerCharacter != nullptr)
	{
		CurrentSpeed	= PlayerCharacter->GetVelocity().Size();
		IsInAir			= PlayerCharacter->GetMovementComponent()->IsFalling();
	}
}