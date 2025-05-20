// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "KSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UGameOverWidget::GameOver1()
{
	PlayAnimation(GameOverAnimation);
}

void UGameOverWidget::GameOver2()
{
	PlayAnimation(GameOverAnimation);
	GameOverText2->SetText(FText::FromString("No Money"));
}

void UGameOverWidget::GameClear()
{
	IsClear = true;
	UGameplayStatics::PlaySound2D(GetWorld(), GameClearSound);
	GameOverText1->SetText(FText::FromString("Game Clear"));
	GameOverText2->SetText(FText::FromString("Congratulations"));

	PlayAnimation(GameClearAnimation);
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
	if (IsClear) PlayAnimation(BeforeNewSceneAnimation2);
	else PlayAnimation(BeforeNewSceneAnimation);
	RestartB->SetIsEnabled(false);
	EndB->SetIsEnabled(false);

	KSGameModeBase->Restart();
}

void UGameOverWidget::End()
{
	if (IsClear) PlayAnimation(BeforeNewSceneAnimation2);
	else PlayAnimation(BeforeNewSceneAnimation);
	RestartB->SetIsEnabled(false);
	EndB->SetIsEnabled(false);

	KSGameModeBase->End();
}