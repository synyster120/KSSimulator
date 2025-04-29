// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Ingredient.generated.h"

/**
 * 
 */

USTRUCT()
struct FIngredientInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	int32 Price;
};

UCLASS()
class KSSIMULATOR_API UIngredient : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FIngredientInfo> Items;

	//image, etc
};
