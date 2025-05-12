// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FoodCountWidget.generated.h"

/**
 * 
 */
UCLASS()
class KSSIMULATOR_API UFoodCountWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* FoodName;
	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* FoodCount;
};
