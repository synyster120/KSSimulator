// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InputActionValue.h"
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
	TSubclassOf<class UMainWidget> MainUIClass;

	//UPROPERTY(VisibleAnywhere)
	class UMainWidget* MainUI;

private:
	int32 Money = 10000;
	int32 WorldTime = 0;
	int32 Level = 1;
	float Rating = 4.0f;

public:
	void SetMoney(int32 M);
	int32 GetMoney();
	void SetRating(float R);
	float GetRating();
};
