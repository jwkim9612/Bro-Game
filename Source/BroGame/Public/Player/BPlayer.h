// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Character.h"
#include "BPlayer.generated.h"

UCLASS()
class BROGAME_API ABPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;
};
