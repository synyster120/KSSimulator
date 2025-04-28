// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class KSSIMULATOR_API UGameMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* MoneyValue;
};
