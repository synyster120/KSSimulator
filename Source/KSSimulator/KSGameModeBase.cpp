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

	Money = 0;

	if (MainUIClass != nullptr)
	{
		MainUI = CreateWidget<UGameMainWidget>(GetWorld(), MainUIClass);
		if (MainUI)
		{
			MainUI->AddToViewport();
			SetMoney(0);
			NewDay();
		}
	}
}

void AKSGameModeBase::NewDay()
{
	Time = 500;

	SetMoney(0);
	UpdateTime();
	
	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKSGameModeBase::UpdateTime, 10.0f, true);
}

void AKSGameModeBase::UpdateTime()
{
	Time += 10;

	TimeStr = FString::Printf(TEXT("%02d"), Time < 780 ? Time / 60 : (Time - 780) / 60)
		+ ":" + FString::Printf(TEXT("%02d"), Time % 60) 
		+ FString::Printf(TEXT(" %s"), Time >= 720 ? TEXT("PM") : TEXT("AM"));
	UE_LOG(LogTemp, Warning, TEXT("%d, %s"), Time, *TimeStr);
	if (MainUI)
	{
		MainUI->Time->SetText(FText::FromString(TimeStr));
	}
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
