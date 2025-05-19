#include "KSGameModeBase.h"
#include "GameMainWidget.h"
#include "Widgets/OrderingWidget.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "FadeInOutWidget.h"
#include "FoodCountActor.h"
#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"

#include "HAL/PlatformTime.h"
#include "Misc/DateTime.h"
#include "Tickable.h"
#include "Containers/Ticker.h"

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

	static ConstructorHelpers::FClassFinder<UGameOverWidget> d(TEXT("/Game/Widgets/BP_GameOverWidget.BP_GameOverWidget_C"));
	if (d.Succeeded())
	{
		GOClass = d.Class;
	}
}

void AKSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(this, 0);
	OrderManager = NewObject<UOrderManager>(this);
	Money = 50000;
	for (int32 i = 0;i < 4;i++) 
	{
		FoodCount[i] = 15;
		for (int32 j = 0;j < 15;j++) {
			FoodQ[i].Enqueue(1);
		}
		FoodToday[i] = 15;
	}

	FoodCountActor = GetWorld()->SpawnActor<AFoodCountActor>(FoodCountActorClass, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
	FoodCountActor->SetActorLocation(FVector(0.f, 0.f, 0.f));
	if (MainUIClass != nullptr)
	{
		MainUI = CreateWidget<UGameMainWidget>(GetWorld(), MainUIClass);
		if (MainUI)
		{
			OrderManager->SetWidget(MainUI);
			MainUI->AddToViewport(3);
			SetMoney(0);
			NewDay();
		}
	}
}

void AKSGameModeBase::NewDay()
{
	Day += 1;
	MainUI->DayText->SetText(FText::FromString(FString::Printf(TEXT("Day %d"), Day)));
	MainUI->OrderText->SetText(FText::FromString("Orders"));
	IsOpen = false;

	UClass* BPClass = LoadClass<AActor>(nullptr, TEXT("/Game/Blueprints/BP_KSSPlayer.BP_KSSPlayer_C"));
	if (!BPClass) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPClass, FoundActors);

	if (FoundActors.Num() > 0)
	{
		AActor* BPInstance = FoundActors[0];
		APawn* Pawn = Cast<APawn>(BPInstance);
		AController* Controller = Pawn->GetController();

		Controller->SetControlRotation(FRotator(0.f, 90.f, 0.f));
		BPInstance->SetActorLocation(FVector(1040.f, -1630.f, 448.f));
	}

	for (int32 i = 0; i < 4;i++)
	{
		if (FoodToday[i] < FoodCount[i])
		{
			for (int32 j = 0;j < FoodCount[i] - FoodToday[i];j++)
			{
				FoodQ[i].Enqueue(Day);
			}
		}
		FoodToday[i] = FoodCount[i];
		IsTableFull[i] = false;
	}

	if (OW)
	{
		OW->RemoveFromParent();
	}
	if (FIO)
	{
		FIO->FadeIn();
	}
	else
	{
		FIO = CreateWidget<UFadeInOutWidget>(GetWorld(), FIOClass);
		FIO->AddToViewport(4);
		FIO->FadeIn();
	}
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
	TimeDilationSet(1.f);

	Time = 530;
	SetMoney(0);
	UpdateTime();

	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().ClearTimer(FadeHandle);
	GetWorldTimerManager().SetTimer(FadeHandle, this, &AKSGameModeBase::FadeInFin, 2.5f, false);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKSGameModeBase::UpdateTime, 3.f, true);
}

void AKSGameModeBase::FadeInFin()
{
	if (FIO)
	{
		FIO->RemoveFromParent();
		FIO = nullptr;
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
		MainUI->MoneyValue->SetText(FText::AsNumber(Money));
	}
	if (M > 0) UGameplayStatics::PlaySound2D(GetWorld(), MoneySound);
	if (Money > 200000)
	{
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());
		}
		TimeDilationSet(0.f);
		GameClear();
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
	if (Rating < 3.f)
	{
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());
		}
		TimeDilationSet(0.f);
		GameOver();
	}
}

float AKSGameModeBase::GetRating()
{
	return Rating;
}

void AKSGameModeBase::SetIngreCount(int32 Index, int32 Value)
{
	FoodCount[Index] += Value;

	if (FoodCountActor)
	{
		FoodCountActor->SetFoodCount(Index, FoodCount[Index]);
	}
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
	if (FIOClass)
	{
		FIO = CreateWidget<UFadeInOutWidget>(GetWorld(), FIOClass);
		FIO->AddToViewport(4);
		FIO->FadeOut();
	}

	GetWorldTimerManager().ClearTimer(FadeHandle);
	GetWorldTimerManager().SetTimer(FadeHandle, this, &AKSGameModeBase::EndDay, 2.5f, false);
}

void AKSGameModeBase::EndDay()
{
	TimeDilationSet(0.f);

	OrderManager->EndDay();

	UWorld* World = GetWorld();
	if (!World) return;

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->Tags.Contains("DBP"))
		{
			Actor->Destroy();
		}
	}

	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < FoodToday[i] - FoodCount[i];j++)
		{
			FoodQ[i].Pop();
		}
		int32 FV;
		while (FoodQ[i].Peek(FV) && FV == Day - 1)
		{
			FoodQ[i].Pop();
			FoodCount[i] -= 1;
		}
		FoodToday[i] = FoodCount[i];
		FoodCountActor->SetFoodCount(i, FoodToday[i]);
	}

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}

	if (OWClass != nullptr)
	{
		OW = CreateWidget<UOrderingWidget>(GetWorld(), OWClass);
		OW->AddToViewport(2);
	}
	if (MainUI)
	{
		MainUI->Time->SetText(FText::FromString(""));
		MainUI->DayText->SetText(FText::FromString(""));
		MainUI->OrderText->SetText(FText::FromString(""));
	}
	if (FIO)
	{
		FIO->RemoveFromParent();
		FIO->AddToViewport(1);
	}
}

void AKSGameModeBase::GameOver()
{
	if (MainUI) MainUI->RemoveFromParent();
	if (OW) OW->RemoveFromParent();
	if (FIO) FIO->RemoveFromParent();
	GO = CreateWidget<UGameOverWidget>(GetWorld(), GOClass);
	GO->AddToViewport(5);
	GO->FadeOut();
}

void AKSGameModeBase::GameClear()
{
	if (MainUI) MainUI->RemoveFromParent();
	if (OW) OW->RemoveFromParent();
	if (FIO) FIO->RemoveFromParent();
	GO = CreateWidget<UGameOverWidget>(GetWorld(), GOClass);
	GO->AddToViewport(5);
	GO->GameClear();
}

void AKSGameModeBase::Restart()
{
	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda([this](float DeltaTime)
			{
				FName CurrentLevel = *UGameplayStatics::GetCurrentLevelName(this, true);
				UGameplayStatics::OpenLevel(this, CurrentLevel);
				return false;
			}),
		1.0f
	);
}

void AKSGameModeBase::End()
{
	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda([this](float DeltaTime)
			{
				UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
				return false;
			}),
		1.0f
	);
}