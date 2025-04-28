// Fill out your copyright notice in the Description page of Project Settings.


#include "KSGameModeBase.h"
#include "Widget/MainWidget.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AKSGameModeBase::AKSGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UMainWidget> MainWidgetClass(TEXT("/Game/Widget/BP_MainWidget.BP_MainWidget_C"));
	if (MainWidgetClass.Succeeded())
	{
		MainUIClass = MainWidgetClass.Class;
	}
}

void AKSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetMoney(500);
	SetRating(0.5f);

	if (MainUIClass != nullptr)
	{
		MainUI = CreateWidget<UMainWidget>(GetWorld(), MainUIClass);
		if (MainUI)
		{
			MainUI->AddToViewport();
			MainUI->MoneyValue->SetText(FText::AsNumber(GetMoney()));
		}
	}
}

void AKSGameModeBase::SetMoney(int32 M)
{
	Money += M;
	MainUI->MoneyValue->SetText(FText::AsNumber(GetMoney()));
}

int32 AKSGameModeBase::GetMoney()
{
	return Money;
}

void AKSGameModeBase::SetRating(float R)
{
	Rating += R;
}

float AKSGameModeBase::GetRating()
{
	return Rating;
}
