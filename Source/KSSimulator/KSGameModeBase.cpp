#include "KSGameModeBase.h"
#include "GameMainWidget.h"
#include "Widgets/OrderingWidget.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AKSGameModeBase::AKSGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UGameMainWidget> a(TEXT("/Game/Widgets/BP_GameMainWidget.BP_GameMainWidget_C"));
	if (a.Succeeded())
	{
		MainUIClass = a.Class;
	}

	static ConstructorHelpers::FClassFinder<UOrderingWidget> b(TEXT("/Game/Widgets/BP_OrderingWidget.BP_OrderingWidget_C"));
	if (b.Succeeded())
	{
		OWClass = b.Class;
	}
}

void AKSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(this, 0);
	Money = 50000;
	for (int32 i = 0;i < 5;i++) FoodCount[i] = 10;

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
	Day += 1;

	if (OW)
	{
		OW->RemoveFromViewport();
	}
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
	TimeDilationSet(1.f);

	Time = 500;
	SetMoney(0);
	UpdateTime();
	
	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKSGameModeBase::UpdateTime, 1.f, true);
}

void AKSGameModeBase::UpdateTime()
{
	Time += 10;

	TimeStr = FString::Printf(TEXT("%02d"), Time < 780 ? Time / 60 : (Time - 720) / 60)
		+ ":" + FString::Printf(TEXT("%02d"), Time % 60) 
		+ FString::Printf(TEXT(" %s"), Time >= 720 ? TEXT("PM") : TEXT("AM"));
	UE_LOG(LogTemp, Warning, TEXT("%d, %s"), Time, *TimeStr);
	if (MainUI)
	{
		MainUI->Time->SetText(FText::FromString(TimeStr));
	}

	if (Time == 1080)
	{
		BeforeEndDay();
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

void AKSGameModeBase::SetIngreCount(int32 Index, int32 Value)
{
	FoodCount[Index] = Value;
}

int32 AKSGameModeBase::GetIngreCount(int32 Index)
{
	return FoodCount[Index];
}

void AKSGameModeBase::TimeDilationSet(float T)
{
	GetWorldSettings()->SetTimeDilation(T);
}

void AKSGameModeBase::BeforeEndDay()
{
	TimeDilationSet(0.f);

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}

	if (OWClass != nullptr)
	{
		OW = CreateWidget<UOrderingWidget>(GetWorld(), OWClass);
		if (OW) OW->AddToViewport();
		if (MainUI)
		{
			MainUI->RemoveFromViewport();
			MainUI->AddToViewport();
			MainUI->Time->SetText(FText::FromString(""));
		}
	}
}
