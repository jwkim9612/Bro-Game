// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "HUD/BInterfaceWidgetBase.h"
#include "BStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBStatWidget : public UBInterfaceWidgetBase
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
};
