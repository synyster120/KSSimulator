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
	ImageSet();
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

void UOrderBoxWidget::ImageSet()
{
	UTexture2D* NewTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Content/MapAsset/UI/ys.uasset"));

	if (Image && NewTexture)
	{
		UE_LOG(LogTemp, Warning, TEXT("HI"));
		Image->SetBrushFromTexture(NewTexture);
	}
}
