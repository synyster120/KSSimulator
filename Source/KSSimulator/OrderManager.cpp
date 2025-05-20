// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderManager.h"

void UOrderManager::NewDay()
{
	OI.Empty();
    OrderTextBlocks.Empty();
    GameMainWidget->OrderListBox->ClearChildren();
	OrderNumber = 0;
}

int32 UOrderManager::OrderIn(int32 TableNum, int32 FoodNum)
{
    int32 ReturnOrderNum = OrderNumber;
	OI.Add(FOrderInfo(OrderNumber++, TableNum, FoodNum));

    UTextBlock* NewText = NewObject<UTextBlock>(this);
    if (NewText)
     {
        NewText->SetText(FText::FromString(FString::Printf(TEXT("%d번 테이블 수육 국밥"), TableNum)));
        NewText->Font.Size = 20;
        GameMainWidget->OrderListBox->AddChildToVerticalBox(NewText);
        OrderTextBlocks.Add(NewText);
    }
    return ReturnOrderNum;
}

void UOrderManager::OrderOut(int32 OrderNum)
{
    for (int32 i = 0; i < OI.Num(); ++i)
    {
        if (OI[i].OrderNum == OrderNum)
        {
            if (OrderTextBlocks.IsValidIndex(i))
            {
                if (GameMainWidget && GameMainWidget->OrderListBox)
                {
                    GameMainWidget->OrderListBox->RemoveChild(OrderTextBlocks[i]);
                }
                OrderTextBlocks.RemoveAt(i);
            }
            OI.RemoveAt(i);
            break;
        }
    }
}

void UOrderManager::EndDay()
{
    for (UTextBlock* TextBlock : OrderTextBlocks)
    {
        GameMainWidget->OrderListBox->RemoveChild(TextBlock);
    }
    OrderTextBlocks.Empty();
}

void UOrderManager::SetWidget(UGameMainWidget* InWidget)
{
    GameMainWidget = InWidget;
}