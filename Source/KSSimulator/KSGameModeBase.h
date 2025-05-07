// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	//UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UGameMainWidget> MainUIClass;

	//UPROPERTY(VisibleAnywhere)
	class UGameMainWidget* MainUI;

private:
	int32 Money;
	int32 WorldTime = 0;
	int32 Level = 1;
	float Rating = 4.0f;
	int32 Time = 0;
	FString TimeStr;

	FTimerHandle TimerHandle;

	void NewDay();
	void UpdateTime();

public:
	UFUNCTION(BlueprintCallable) // 블루프린트에서 사용가능한 함수로 지정
		void SetMoney(int32 M);

	int32 GetMoney();
	void SetRating(float R);
	float GetRating();
};