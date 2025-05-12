// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KSSimulator/KSGameModeBase.h"
#include "KSSimulator/Ingredient.h"
#include "OrderBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class KSSIMULATOR_API UOrderBoxWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* Value;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UButton* Minus;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UButton* Plus;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* Name;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image;

	AKSGameModeBase* KSGameModeBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UIngredient* Ingre;

	int32 Min = 0;
	int32 Now = 0;
	int32 Price = 0;
	int32 Num = 0;

	virtual void NativeConstruct();
	void NewBox(int32 ID);
	UFUNCTION()
	void PressL();
	UFUNCTION()
	void PressR();
	void ImageSet(int32 N);
};
