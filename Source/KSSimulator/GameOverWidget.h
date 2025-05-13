// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KSGameModeBase.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class KSSIMULATOR_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UButton* RestartB;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* RestartBT;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UButton* EndB;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* EndBT;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* GameOverText1;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UTextBlock* GameOverText2;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UBorder* GameOverBorder;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* GameOverAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* BeforeNewSceneAnimation;

	void FadeOut();

	AKSGameModeBase* KSGameModeBase;

	virtual void NativeConstruct();

	UFUNCTION()
	void Restart();
	UFUNCTION()
	void End();
};
