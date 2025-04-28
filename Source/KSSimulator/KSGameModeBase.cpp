#include "KSGameModeBase.h"
#include "GameMainWidget.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"

AKSGameModeBase::AKSGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UGameMainWidget> a(TEXT("/Game/Widgets/BP_GameMainWidget.BP_GameMainWidget_C"));
	if (a.Succeeded())
	{
		MainUIClass = a.Class;
	}
}

void AKSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetMoney(500);
	SetRating(0.5f);

	if (MainUIClass != nullptr)
	{
		MainUI = CreateWidget<UGameMainWidget>(GetWorld(), MainUIClass);
		if (MainUI)
		{
			MainUI->AddToViewport();
			MainUI->MoneyValue->SetText(FText::AsNumber(GetMoney()));
		}
	}
	SetMoney(1000);
}

void AKSGameModeBase::SetMoney(int32 M)
{
	Money += M;

	if (MainUI)
	{
		MainUI->MoneyValue->SetText(FText::AsNumber(GetMoney()));
	}
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
