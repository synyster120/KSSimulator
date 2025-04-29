// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Food.generated.h"

USTRUCT()
struct FFoodInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 FoodID;

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	int32 Price;

	UPROPERTY(EditAnywhere)
	TArray<int32> Ingredients;
};

UCLASS()
class KSSIMULATOR_API UFood : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FFoodInfo> Items;
};
