// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerMaker.h"
#include "Kismet/GameplayStatics.h"


UCustomerMaker::UCustomerMaker(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UCustomerMaker::GameModeIn(AKSGameModeBase* AKSG)
{
	KSGameModeBase = AKSG;
	KSGameModeBase->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCustomerMaker::Make, 5.f, true);
}

void UCustomerMaker::Make()
{
	for (int32 i = 1;i < 5;i++)
	{
		if (!GetTable(i))
		{
			SetTable(i);
			FVector SpawnLocation = FVector(Vec[i][0], Vec[i][1], 50.f);
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			ACustomer* NewCustomer = KSGameModeBase->GetWorld()->SpawnActor<ACustomer>(
				CustomerClass,
				SpawnLocation,
				SpawnRotation,
				SpawnParams
			);

			if (NewCustomer)
			{
				NewCustomer->Hi(i, this);
				Cu[i] = NewCustomer;
			}
			break;
		}
	}

	KSGameModeBase->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCustomerMaker::Make, 5.f, true);
}

bool UCustomerMaker::GetTable(int32 TNum)
{
	return KSGameModeBase->GetTable(TNum);
}

void UCustomerMaker::SetTable(int32 TNum)
{
	KSGameModeBase->SetTable(TNum);
}

void UCustomerMaker::PayMoney(int32 Money)
{
	KSGameModeBase->SetMoney(Money);
}
