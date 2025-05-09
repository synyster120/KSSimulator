// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KSSimulator/KSGameModeBase.h"
#include "Customer.h"
#include "CustomerMaker.generated.h"

/**
 * 
 */
UCLASS()
class KSSIMULATOR_API UCustomerMaker : public UObject
{
	GENERATED_BODY()
	
public:
	AKSGameModeBase* KSGameModeBase;
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ACustomer> CustomerClass;
	ACustomer* Cu[5];
	float Vec[5][2] = { {0.f,0.f},{50.f,50.f},{50.f,-50.f},{-50.f,50.f}, {-50.f,-50.f} };

public:
	UCustomerMaker(const FObjectInitializer& ObjectInitializer);
	void GameModeIn(AKSGameModeBase* AKSG);
	void Make();

	bool GetTable(int32 TNum);
	void SetTable(int32 TNum);
	void PayMoney(int32 Money);
};
