// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderBoxWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

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
	ImageSet(ID);
	Name->SetText(FText::FromString(Ingre->Items[ID].Name));
	Value->SetText(FText::AsNumber(Now));
	if (Now == Min)
	{
		Minus->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UOrderBoxWidget::PressL()
{
	if (Now > Min) {
		Now--;
		Value->SetText(FText::AsNumber(Now));
		KSGameModeBase->SetMoney(Price);
		KSGameModeBase->SetIngreCount(Num, -1);
		if (Now == Min)
		{
			Minus->SetVisibility(ESlateVisibility::Hidden);

		}
	}
}

void UOrderBoxWidget::PressR()
{
	if (Now == Min)
	{
		Minus->SetVisibility(ESlateVisibility::Visible);
	}
	if (KSGameModeBase->GetMoney()>=500)
	{
		Now++;
		Value->SetText(FText::AsNumber(Now));

		KSGameModeBase->SetMoney(-Price);
		KSGameModeBase->SetIngreCount(Num, 1);
	}
}

void UOrderBoxWidget::ImageSet(int32 N)
{
	UTexture2D* NewTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/MapAsset/UI/ys.ys"));
	switch (N) 
	{
	case 1:
		NewTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/MapAsset/UI/bc.bc")); break;
	case 2:
		NewTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/MapAsset/UI/ddg.ddg")); break;
	case 3:
		NewTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/MapAsset/UI/sy.sy")); break;
	}

	if (Image && NewTexture)
	{
		Image->SetBrushFromTexture(NewTexture);
	}
}
