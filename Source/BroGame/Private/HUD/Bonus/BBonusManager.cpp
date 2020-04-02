// Fill out your copyright notice in the Description page of Project Settings.


#include "BBonusManager.h"
#include "BGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "..\..\..\Public\HUD\Bonus\BBonusManager.h"

UBBonusManager::UBBonusManager()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D>
		MaxHP_Texture(TEXT("Texture2D'/Game/GameData/Interface/MaxHP.MaxHP'"));

	if (MaxHP_Texture.Succeeded())
	{
		MaxHPTexture = MaxHP_Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		Speed_Texture(TEXT("Texture2D'/Game/GameData/Interface/Speed.Speed'"));

	if (Speed_Texture.Succeeded())
	{
		SpeedTexture = Speed_Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		Money_Texture(TEXT("Texture2D'/Game/GameData/Coin/Coin.Coin'"));

	if (Money_Texture.Succeeded())
	{
		MoneyTexture = Money_Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		Combo_Texture(TEXT("Texture2D'/Game/GameData/Interface/Combo.Combo'"));

	if (Combo_Texture.Succeeded())
	{
		ComboTexture = Combo_Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		HPRecovery_Texture(TEXT("Texture2D'/Game/GameData/Interface/HPRecovery.HPRecovery'"));

	if (HPRecovery_Texture.Succeeded())
	{
		HPRecoveryTexture = HPRecovery_Texture.Object;
	}
}

void UBBonusManager::Init()
{

	UBGameInstance* BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BCHECK(BGameInstance != nullptr);

	UDataTable* BonusDataTable = BGameInstance->GetBonusDataTable();
	BCHECK(BonusDataTable != nullptr);

	FString Context;
	BonusDataTable->GetAllRows<FBBonusInfo>(Context, AllBonusInfo);

	// 각각의 레어리티 어레이에 대입
	for (auto& BonusInfo : AllBonusInfo)
	{
		switch (BonusInfo->Rarelity)
		{
		case EBonusRarelity::Normal:
			Normals.Add(*BonusInfo);
			break;

		case EBonusRarelity::Rare:
			Rares.Add(*BonusInfo);
			break;

		case EBonusRarelity::Unique:
			Uniques.Add(*BonusInfo);
			break;

		case EBonusRarelity::Legend:
			Legends.Add(*BonusInfo);
			break;
		}
	}

	// 이미지 초기화
}

FBBonusInfo UBBonusManager::GetRandomBonus()
{
	float RandomNum = UKismetMathLibrary::RandomFloat();
	
	EBonusRarelity RandomRarelity = GetRarelityByNum(RandomNum);

	return GetRandomBonusInfo(RandomRarelity);

	//// 예외처리해주기. 나중에 할것.
	//return FBBonusInfo();
}

FBBonusInfo UBBonusManager::GetRandomBonusByRarelity(EBonusRarelity Rarelity)
{
	return GetRandomBonusInfo(Rarelity);

	//// 예외처리해주기. 나중에 할것.
	//return FBBonusInfo();
}

UTexture2D * UBBonusManager::GetMaxHPTexture() const
{
	return MaxHPTexture;
}

UTexture2D * UBBonusManager::GetSpeedTexture() const
{
	return SpeedTexture;
}

UTexture2D * UBBonusManager::GetMoneyTexture() const
{
	return MoneyTexture;
}

UTexture2D * UBBonusManager::GetComboTexture() const
{
	return ComboTexture;
}

UTexture2D * UBBonusManager::GetHPRecoveryTexture() const
{
	return HPRecoveryTexture;
}

bool UBBonusManager::IsInNormalRange(float Num)
{
	if (0.6f >= Num && Num >= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBBonusManager::IsInRareRange(float Num)
{
	if (0.9f >= Num && Num > 0.6f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBBonusManager::IsInUniqueRange(float Num)
{
	if (0.99f >= Num && Num > 0.9f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBBonusManager::IsInLegendRange(float Num)
{
	if (0.99 < Num)
	{
		return true;
	}
	else
	{
		return false;
	}
}

EBonusRarelity UBBonusManager::GetRarelityByNum(float Num)
{
	if (Num > 1 || Num < 0)
	{
		BLOG(Warning, TEXT("Error"));
	}

	if (IsInNormalRange(Num))
	{
		return EBonusRarelity::Normal;
	}
	else if (IsInRareRange(Num))
	{
		return EBonusRarelity::Rare;
	}
	else if (IsInUniqueRange(Num))
	{
		return EBonusRarelity::Unique;
	}
	else if (IsInLegendRange(Num))
	{
		return EBonusRarelity::Legend;
	}

	// 후에 바꿔야함. try catch 등.
	return EBonusRarelity::Normal;
}

FBBonusInfo UBBonusManager::GetRandomBonusInfo(EBonusRarelity Rarelity)
{
	int32 RandomIndex;
	switch (Rarelity)
	{
	case EBonusRarelity::Normal:
		RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, Normals.Num() - 1);
		return Normals[RandomIndex];
		break;
	case EBonusRarelity::Rare:
		RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, Rares.Num() - 1);
		return Rares[RandomIndex];
		break;
	case EBonusRarelity::Unique:
		RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, Uniques.Num() - 1);
		return Uniques[RandomIndex];
	case EBonusRarelity::Legend:
		RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, Legends.Num() - 1);
		return Legends[RandomIndex];
		break;
	}

	// 예외처리해주기. 나중에 할것.
	return FBBonusInfo();
}
