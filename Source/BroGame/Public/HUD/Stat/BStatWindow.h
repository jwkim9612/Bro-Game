// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "HUD/BWindowBase.h"
#include "BStatWindow.generated.h"

USTRUCT()
struct FBStatInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	UTexture2D* Image;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	EStat Stat;
};

/**
 * 
 */
UCLASS()
class BROGAME_API UBStatWindow : public UBWindowBase
{
	GENERATED_BODY()
	
public:
	void Init(class UBInterfaceWidgetBase* InterfaceWidget) override;

private:
	UPROPERTY(EditAnywhere, Category = "Info")
	TArray<struct FBStatInfo> BStatInfo;

	UPROPERTY()
	TArray<class UBStatSlot*> BStats;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox;
};
