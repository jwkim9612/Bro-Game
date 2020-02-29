// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Uobject/Object.h"
#include "BBonusManager.generated.h"



/**
 * 
 */
UCLASS()
class BROGAME_API UBBonusManager : public UObject
{
	GENERATED_BODY()

public:
	UBBonusManager();

public:
	void Init();
	struct FBBonusInfo GetRandomBonus();

	class UTexture2D* GetAttackTexture() const;
	class UTexture2D* GetMaxHPTexture() const;
	class UTexture2D* GetSpeedTexture() const;
	class UTexture2D* GetMoneyTexture() const;

private:
	bool IsInNormalRange(float Num);
	bool IsInRareRange(float Num);
	bool IsInUniqueRange(float Num);
	bool IsInLegendRange(float Num);
	EBonusRarelity GetRarelityByNum(float Num);

private:
	TArray<struct FBBonusInfo*> AllBonusInfo;

	UPROPERTY()
	TArray<struct FBBonusInfo> Normals;

	UPROPERTY()
	TArray<struct FBBonusInfo> Rares;

	UPROPERTY()
	TArray<struct FBBonusInfo> Uniques;

	UPROPERTY()
	TArray<struct FBBonusInfo> Legends;

	UPROPERTY(EditDefaultsOnly, Category = "Image")
	class UTexture2D* AttackTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Image")
	class UTexture2D* MaxHPTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Image")
	class UTexture2D* SpeedTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Image")
	class UTexture2D* MoneyTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Image")
	class UTexture2D* ComboTexture;


};
