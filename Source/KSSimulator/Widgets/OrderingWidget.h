	// Fill out your copyright notice in the Description page of Project Settings.

	#pragma once

	#include "CoreMinimal.h"
	#include "Blueprint/UserWidget.h"
	#include "OrderBoxWidget.h"
	#include "Components/ScrollBox.h"
	#include "KSSimulator/Food.h"
	#include "Components/Button.h"
	#include "OrderingWidget.generated.h"

	/**
	 * 
	 */
	UCLASS()
	class KSSIMULATOR_API UOrderingWidget : public UUserWidget
	{
		GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UFood* Fo;

		UPROPERTY(EditAnywhere, meta = (BindWidget));
		class UButton* NextButton;

		virtual void NativeConstruct();
		void Refresh();
		UFUNCTION()
		void NextDay();
		UPROPERTY(EditAnywhere)
		class USoundBase* ClickSound;

	protected:
		UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UScrollBox* OrderScrollBox;
	
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Order")
		TSubclassOf<class UOrderBoxWidget> BoxClass;
		UOrderBoxWidget* Box[5];

		AKSGameModeBase* KSGameModeBase;

		void ClickSoundPlayer();
	};
