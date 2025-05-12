// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "KSGameModeBase.h"
#include "FoodCountActor.generated.h"

UCLASS()
class KSSIMULATOR_API AFoodCountActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodCountActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AKSGameModeBase* KSGameModeBase;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UFoodCountWidget> FoodCountWidgetClass;
	UPROPERTY()
	TArray<UWidgetComponent*> WidgetComponents;
	UPROPERTY()
	TArray<UFoodCountWidget*> FoodCountWidgets;
	UPROPERTY()
	UFoodCountWidget* FoodWidget;

	UPROPERTY(EditAnywhere)
	int32 WidgetCount = 4;

public:
	void SetFoodCount(int32 Index, int32 Value);
};
