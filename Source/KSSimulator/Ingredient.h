// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Ingredient.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FIngredientInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Price;
};

UCLASS(BlueprintType)
class KSSIMULATOR_API UIngredient : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FIngredientInfo> Items;

	//image, etc
};
