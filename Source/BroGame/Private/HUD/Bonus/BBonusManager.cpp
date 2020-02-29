// Fill out your copyright notice in the Description page of Project Settings.


#include "BBonusManager.h"
#include "BGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "..\..\..\Public\HUD\Bonus\BBonusManager.h"

UBBonusManager::UBBonusManager()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D>
		Attack_Texture(TEXT("Texture2D'/Game/GameData/Interface/fight.fight'"));

	if (Attack_Texture.Succeeded())
	{
		AttackTexture = Attack_Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		MaxHP_Texture(TEXT("Texture2D'/Game/GameData/Interface/hp.hp'"));

	if (MaxHP_Texture.Succeeded())
	{
		MaxHPTexture = MaxHP_Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		Speed_Texture(TEXT("Texture2D'/Game/GameData/Interface/sprinter.sprinter'"));

	if (Speed_Texture.Succeeded())
	{
		SpeedTexture = Speed_Texture.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		Money_Texture(TEXT("Texture2D'/Game/GameData/Coin/gold.gold'"));

	if (Money_Texture.Succeeded())
	{
		MoneyTexture = Money_Texture.Object;
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

	// ������ ���Ƽ ��̿� ����
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

	// �̹��� �ʱ�ȭ
}

FBBonusInfo UBBonusManager::GetRandomBonus()
{
	float RandomNum = UKismetMathLibrary::RandomFloat();
	
	EBonusRarelity RandomRarelity = GetRarelityByNum(RandomNum);


	int32 RandomIndex;
	switch (RandomRarelity)
	{
	case EBonusRarelity::Normal:
		RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, Normals.Num()-1);
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

	// ����ó�����ֱ�. ���߿� �Ұ�.
	return FBBonusInfo();
}

UTexture2D * UBBonusManager::GetAttackTexture() const
{
	return AttackTexture;
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

	// �Ŀ� �ٲ����. try catch ��.
	return EBonusRarelity::Normal;
}
