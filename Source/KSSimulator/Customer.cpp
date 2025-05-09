// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"
#include "CustomerMaker.h"

// Sets default values
ACustomer::ACustomer()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MMA(TEXT("/Engine/EditorMaterials/WidgetMaterial_X"));
	if (MMA.Succeeded()) MA = MMA.Object;
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MMB(TEXT("/Engine/EditorMaterials/WidgetMaterial_Current"));
	if (MMB.Succeeded()) MB = MMB.Object;
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MMC(TEXT("/Engine/EditorMaterials/WidgetMaterial_Y"));
	if (MMC.Succeeded()) MC = MMC.Object;
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MMD(TEXT("/Engine/EditorMaterials/WidgetMaterial_Z"));
	if (MMD.Succeeded()) MD = MMD.Object;
}

void ACustomer::Hi(int32 InTableNum, UCustomerMaker* CM)
{
	TableNum = InTableNum;
	CustomerMaker = CM;

    GetWorldTimerManager().SetTimer(TimerHandle, this, &ACustomer::RingBell, 5.f, true);
}

void ACustomer::RingBell()
{
	NowStat = 1;
    if (MeshComponent)
    {
		MeshComponent->SetMaterial(0, MA);
    }
}

void ACustomer::Order()
{
	NowStat = 2;
	if (MeshComponent)
	{
		MeshComponent->SetMaterial(0, MB);
	}
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACustomer::GetFood, 5.f, true);
}

void ACustomer::GetFood()
{
	NowStat = 3;
	if (MeshComponent)
	{
		MeshComponent->SetMaterial(0, MC);
	}
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACustomer::FinishFood, 5.f, true);
}

void ACustomer::FinishFood()
{
	NowStat = 4;
	CustomerMaker->SetTable(TableNum);
	CustomerMaker->PayMoney(10000);
	this->Destroy();
}

int32 ACustomer::GetStat()
{
	return NowStat;
}

