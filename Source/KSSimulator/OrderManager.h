// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "OrderManager.generated.h"

/**
 * 
 */
USTRUCT()
struct FOrderInfo {
	GENERATED_BODY()

	int32 OrderNum;
	int32 TableNum;
	int32 FoodNum;
};

UCLASS()
class KSSIMULATOR_API UOrderManager : public UObject
{
	GENERATED_BODY()
	
private:
	int32 OrderNumber = 0;

	UPROPERTY()
	TArray<FOrderInfo> OI;

	UPROPERTY()
	class UGameMainWidget* GameMainWidget;
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* OrderText;

	TArray<UTextBlock*> OrderTextBlocks; 

	void SetWidget(UGameMainWidget* InWidget);
	void NewDay();
	int32 OrderIn(int32 TableNum, int32 FoodNum);
	void OrderOut(int32 OrderNum);
	void EndDay();
};
