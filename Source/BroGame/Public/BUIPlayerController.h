// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/PlayerController.h"
#include "BUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
