// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "KSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UGameOverWidget::FadeOut()
{
	PlayAnimation(GameOverAnimation);
}

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KSGameModeBase = Cast<AKSGameModeBase>(GetWorld()->GetAuthGameMode());

	if (RestartB)
	{
		RestartB->OnClicked.AddDynamic(this, &UGameOverWidget::Restart);
	}
	if (EndB)
	{
		EndB->OnClicked.AddDynamic(this, &UGameOverWidget::End);
	}
}

void UGameOverWidget::Restart()
{
	PlayAnimation(BeforeNewSceneAnimation);
	RestartB->SetIsEnabled(false);
	EndB->SetIsEnabled(false);

	KSGameModeBase->Restart();
}

void UGameOverWidget::End()
{
	PlayAnimation(BeforeNewSceneAnimation);
	RestartB->SetIsEnabled(false);
	EndB->SetIsEnabled(false);

	KSGameModeBase->End();
}