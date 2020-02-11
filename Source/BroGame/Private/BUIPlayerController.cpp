// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIPlayerController.h"

void ABUIPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}