// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ingredient.h"
#include "Food.h"
#include "OrderManager.h"
#include "Customer.h"
#include "KSPlayer.h"
#include "PlayerHUD.h"
#include "KSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KSSIMULATOR_API AKSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKSGameModeBase();

protected:
	virtual void BeginPlay() override;

protected:
	TSubclassOf<class UGameMainWidget> MainUIClass;
	class UGameMainWidget* MainUI;

	TSubclassOf<class UOrderingWidget> OWClass;
	class UOrderingWidget* OW;

private:
	int32 Money;
	int32 WorldTime = 0;
	int32 Level = 1;
	float Rating = 4.0f;
	int32 Time = 0;
	int32 Day = 0;
	FString TimeStr;
	int32 FoodCount[5];
	bool IsOpen = false;
	bool IsTableFull[5];

	FTimerHandle TimerHandle;
	APlayerController* PC;
	APlayerHUD* MyHUD;
	AKSPlayer* MyPawn;

	void UpdateTime();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
	UFood* Fo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UIngredient* In;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCustomerMaker* CustomerMaker;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACustomer> BP_CustomerClass;
	UPROPERTY()
	UOrderManager* OrderManager;

	void SetMoney(int32 M);
	int32 GetMoney();
	void SetRating(float R);
	float GetRating();
	void SetIngreCount(int32 Index, int32 Value);
	int32 GetIngreCount(int32 Index);
	
	void TimeDilationSet(float T);
	void BeforeEndDay();
	void NewDay();
	
	void SetOpen();
	bool GetOpen();

	void SetTable(int32 TableNum);
	bool GetTable(int32 TableNum);
};