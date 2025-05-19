// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();
	//StartMenuWidgetClass
	//StartMenuWidget
	if (StartGameWidgetClass)
	{
		StartGameWidget = CreateWidget<UUserWidget>(GetWorld(), StartGameWidgetClass);
		if (StartGameWidget)
		{
			StartGameWidget->AddToViewport();

			APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());
		}
	}
}
