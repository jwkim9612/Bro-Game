// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerAnimInstance.h"
#include "BPlayer.h"

UBPlayerAnimInstance::UBPlayerAnimInstance()
{

}

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

void UBPlayerAnimInstance::AnimNotify_CanNextAttack()
{
	OnCanNextAttack.Broadcast();
}

void UBPlayerAnimInstance::AnimNotify_HitAttack()
{
	OnHitAttack.Broadcast();
}

void UBPlayerAnimInstance::PlayGroundAttackMontage()
{
	BCHECK(GroundAttackMontage != nullptr);
	Montage_Play(GroundAttackMontage);
}

void UBPlayerAnimInstance::JumptoNextAttackSection(int32 NewSection)
{
	BCHECK(Montage_IsPlaying(GroundAttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), GroundAttackMontage);
}

FName UBPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
