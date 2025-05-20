// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ingredient.h"
#include "Food.h"
#include "OrderManager.h"
#include "FoodCountWidget.h"
#include "Containers/Queue.h"
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
	UPROPERTY()
	TSubclassOf<class UGameMainWidget> MainUIClass;
	UPROPERTY()
	class UGameMainWidget* MainUI = nullptr;

	UPROPERTY()
	TSubclassOf<class UOrderingWidget> OWClass;
	UPROPERTY()
	class UOrderingWidget* OW = nullptr;

	UPROPERTY()
	TSubclassOf<class UFadeInOutWidget> FIOClass;
	UPROPERTY()
	class UFadeInOutWidget* FIO = nullptr;

	UPROPERTY()
	TSubclassOf<class UGameOverWidget> GOClass;
	UPROPERTY()
	class UGameOverWidget* GO = nullptr;

	class AFoodCountActor* FoodCountActor;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFoodCountActor> FoodCountActorClass;
	TQueue<int32> FoodQ[5];

private:
	int32 Money;
	int32 WorldTime = 0;
	int32 Level = 1;
	float Rating = 4.0f;
	int32 Time = 0;
	int32 Day = 0;
	FString TimeStr;
	int32 FoodCount[5];
	int32 FoodToday[5];
	bool IsTableFull[5];
	bool IsOpen = false;
	bool IsAlive = true;

	FTimerHandle TimerHandle;
	FTimerHandle FadeHandle;
	APlayerController* PC;

	void UpdateTime();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UFood* Fo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UIngredient* In;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UFoodCountWidget> FoodCountWidgetClass;
	UPROPERTY(BlueprintReadOnly)
	UOrderManager* OrderManager;
	UPROPERTY(EditAnywhere)
	class USoundBase* MoneySound;
	

	UFUNCTION(BlueprintCallable)
	void SetMoney(int32 M);
	
	UFUNCTION(BlueprintCallable)
	int32 GetMoney();

	UFUNCTION(BlueprintCallable)
	void SetRating(float R);

	UFUNCTION(BlueprintCallable)
	float GetRating();

	UFUNCTION(BlueprintCallable)
	void SetIngreCount(int32 Index, int32 Value);

	UFUNCTION(BlueprintCallable)
	int32 GetIngreCount(int32 Index);

	void TimeDilationSet(float T);
	void BeforeEndDay();
	void EndDay();
	void NewDay();
	void FadeInFin();

	UFUNCTION(BlueprintCallable)
	void SetOpen();

	UFUNCTION(BlueprintCallable)
	bool GetOpen();

	UFUNCTION(BlueprintCallable)
	void SetTable(int TableNum);

	UFUNCTION(BlueprintCallable)
	bool GetTable(int TableNum);

	void GameOver(int32 OverStat);
	void Restart();
	void End();
};