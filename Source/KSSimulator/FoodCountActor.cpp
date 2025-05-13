// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodCountActor.h"
#include "FoodCountWidget.h"

// Sets default values
AFoodCountActor::AFoodCountActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFoodCountActor::BeginPlay()
{
	Super::BeginPlay();

    KSGameModeBase = Cast<AKSGameModeBase>(GetWorld()->GetAuthGameMode());
	
    for (int32 i = 0; i < WidgetCount; ++i)
    {
        FString Name = FString::Printf(TEXT("WidgetComponent_%d"), i);
        UWidgetComponent* WidgetComp = NewObject<UWidgetComponent>(this, FName(*Name));
        WidgetComp->RegisterComponent();
        WidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        WidgetComp->SetWidgetSpace(EWidgetSpace::World);
        WidgetComp->SetDrawSize(FVector2D(80.f, 60.f));
        WidgetComp->SetTwoSided(true);
        WidgetComp->SetWidgetClass(static_cast<TSubclassOf<UUserWidget>>(FoodCountWidgetClass));
        WidgetComp->InitWidget();
        WidgetComp->SetWorldRotation(FRotator(0.f, 90.f, 0.f));
        switch (i)
        {
        case 0:
            WidgetComp->SetRelativeLocation(FVector(555.f, -1285.f, 600.f)); break;
        case 1:
            WidgetComp->SetRelativeLocation(FVector(-80.f, -1285.f, 500.f)); break;
        case 2:
            WidgetComp->SetRelativeLocation(FVector(20.f, -1285.f, 500.f)); break;
        case 3:
            WidgetComp->SetRelativeLocation(FVector(-180.f, -1285.f, 500.f)); break;
        }
        WidgetComp->SetVisibility(true);

        AddInstanceComponent(WidgetComp);
        WidgetComponents.Add(WidgetComp);

        if (UUserWidget* RawWidget = WidgetComp->GetUserWidgetObject())
        {
            UFoodCountWidget* FCWidget = Cast<UFoodCountWidget>(RawWidget);
            if (FCWidget)
            {
                FoodCountWidgets.Add(FCWidget);
            }

            FString CountString = FString::Printf(TEXT("%d Left"), KSGameModeBase->GetIngreCount(i));
            FoodCountWidgets[i]->FoodCount->SetText(FText::FromString(CountString));
            switch (i)
            {
            case 0:
                FoodCountWidgets[i]->FoodName->SetText(FText::FromString("YukSoo")); break;
            case 1:
                FoodCountWidgets[i]->FoodName->SetText(FText::FromString("BooChoo")); break;
            case 2:
                FoodCountWidgets[i]->FoodName->SetText(FText::FromString("DaDaeGi")); break;
            case 3:
                FoodCountWidgets[i]->FoodName->SetText(FText::FromString("SooYuk")); break;
            }
        }
    }
}

// Called every frame
void AFoodCountActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodCountActor::SetFoodCount(int32 Index, int32 Value)
{
    FString CountString = FString::Printf(TEXT("%d Left"), KSGameModeBase->GetIngreCount(Index));
    FoodCountWidgets[Index]->FoodCount->SetText(FText::FromString(CountString));
}

