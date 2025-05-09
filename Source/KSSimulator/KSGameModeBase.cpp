#include "KSGameModeBase.h"
#include "GameMainWidget.h"
#include "Widgets/OrderingWidget.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "FadeInOutWidget.h"
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

	static ConstructorHelpers::FClassFinder<UFadeInOutWidget> c(TEXT("/Game/Widgets/BP_FadeInOutWidget.BP_FadeInOutWidget_C"));
	if (c.Succeeded())
	{
		FIOClass = c.Class;
	}
}

void AKSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(this, 0);
	OrderManager = NewObject<UOrderManager>(this);
	Money = 50000;
	for (int32 i = 0;i < 5;i++) FoodCount[i] = 10;

	if (MainUIClass != nullptr)
	{
		MainUI = CreateWidget<UGameMainWidget>(GetWorld(), MainUIClass);
		if (MainUI)
		{
			OrderManager->SetWidget(MainUI);
			MainUI->AddToViewport();
			SetMoney(0);
			NewDay();
		}
	}
}

void AKSGameModeBase::NewDay()
{
	Day += 1;
	IsOpen = false;

	for (int32 i = 0; i < 5;i++)
	{
		IsTableFull[i] = false;
	}

	if (OW)
	{
		OW->RemoveFromViewport();
	}
	if (FIOClass != nullptr)
	{
		FIO = CreateWidget<UFadeInOutWidget>(GetWorld(), FIOClass);
		if (FIO)
		{
			FIO->AddToViewport();
			FIO->FadeIn();
		}
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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKSGameModeBase::FadeInFin, 2.5f, true);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKSGameModeBase::UpdateTime, 0.3f, true);
}

void AKSGameModeBase::FadeInFin()
{
	if (FIOClass != nullptr)
	{
		FIO = CreateWidget<UFadeInOutWidget>(GetWorld(), FIOClass);
		if (FIO)
		{
			FIO->RemoveFromViewport();
		}
	}
}

void AKSGameModeBase::SetOpen()
{
	IsOpen = !IsOpen;
}

bool AKSGameModeBase::GetOpen()
{
	return false;
}

void AKSGameModeBase::SetTable(int TableNum)
{
	IsTableFull[TableNum] = !IsTableFull[TableNum];
}

bool AKSGameModeBase::GetTable(int TableNum)
{
	return IsTableFull[TableNum];
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
	if (Time == 550)
	{
		BeforeEndDay();
	}
}

void AKSGameModeBase::SetMoney(int32 M)
{
	Money += M;

	if (MainUI)
	{
		MainUI->MoneyValue->SetText(FText::AsNumber(Money));
	}
}

int32 AKSGameModeBase::GetMoney()
{
	return Money;
}

void AKSGameModeBase::SetRating(float R)
{
	Rating += R;
	if (Rating < 0) Rating = 0;
	else if (Rating > 5) Rating = 5.0f;
	if (MainUI)
	{
		MainUI->RatingValue->SetText(FText::AsNumber(Rating));
	}
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
	if (FIOClass != nullptr)
	{
		FIO = CreateWidget<UFadeInOutWidget>(GetWorld(), FIOClass);
		if (FIO)
		{
			FIO->AddToViewport();
			FIO->FadeOut();
		}
	}

	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKSGameModeBase::EndDay, 2.5f, true);
}

void AKSGameModeBase::EndDay()
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
	if (FIOClass != nullptr)
	{
		FIO = CreateWidget<UFadeInOutWidget>(GetWorld(), FIOClass);
		if (FIO)
		{
			FIO->RemoveFromViewport();
		}
	}
}
