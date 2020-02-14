// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	class ABUIPlayerController* BUIPlayerController;
};
