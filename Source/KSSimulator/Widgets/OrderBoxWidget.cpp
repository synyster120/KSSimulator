// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderBoxWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UOrderBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KSGameModeBase = Cast<AKSGameModeBase>(GetWorld()->GetAuthGameMode());

	if (Minus)
	{
		Minus->OnClicked.AddDynamic(this, &UOrderBoxWidget::PressL);
	}

	if (Plus)
	{
		Plus->OnClicked.AddDynamic(this, &UOrderBoxWidget::PressR);
	}
}

void UOrderBoxWidget::NewBox(int32 ID)
{
	Num = ID;
	Now = KSGameModeBase->GetIngreCount(ID);
	Min = Now;
	Price = Ingre->Items[ID].Price;
	Name->SetText(FText::FromString(Ingre->Items[ID].Name));
	Value->SetText(FText::AsNumber(Now));
}

void UOrderBoxWidget::PressL()
{
	if (Now > Min) {
		Now--;
		Value->SetText(FText::AsNumber(Now));
		KSGameModeBase->SetMoney(Price);
		KSGameModeBase->SetIngreCount(Num, Now);
	}
}

void UOrderBoxWidget::PressR()
{
	if (KSGameModeBase->GetMoney()>=500)
	{
		Now++;
		Value->SetText(FText::AsNumber(Now));

		KSGameModeBase->SetMoney(-Price);
		KSGameModeBase->SetIngreCount(Num, Now);
	}
}