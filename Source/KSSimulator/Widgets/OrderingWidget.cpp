// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderingWidget.h"

void UOrderingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    KSGameModeBase = Cast<AKSGameModeBase>(GetWorld()->GetAuthGameMode());

    if (NextButton)
    {
        NextButton->OnClicked.AddDynamic(this, &UOrderingWidget::NextDay);
    }

    if (BoxClass)
    {
        for (int32 i = 0; i < 5; ++i) // 예시로 5개 추가
        {
            Box[i] = CreateWidget<UOrderBoxWidget>(GetWorld(), BoxClass);
            if (Box[i])
            {
                OrderScrollBox->AddChild(Box[i]);
            }
        }
        Refresh();
    }
}

void UOrderingWidget::Refresh()
{
    for (int32 i = 0;i < 5;i++) {
        Box[i]->NewBox(i);
    }
}

void UOrderingWidget::NextDay()
{
    KSGameModeBase->NewDay();
}
