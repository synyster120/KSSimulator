// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ingredient.h"
#include "Food.h"
#include "OrderManager.h"
#include "FoodCountWidget.h"
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

	TSubclassOf<class UFadeInOutWidget> FIOClass;
	class UFadeInOutWidget* FIO;

	class AFoodCountActor* FoodCountActor;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFoodCountActor> FoodCountActorClass;

private:
	int32 Money;
	int32 WorldTime = 0;
	int32 Level = 1;
	float Rating = 4.0f;
	int32 Time = 0;
	int32 Day = 0;
	FString TimeStr;
	int32 FoodCount[5];
	bool IsTableFull[5];
	bool IsOpen = false;

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
	UPROPERTY()
	UOrderManager* OrderManager;

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
};