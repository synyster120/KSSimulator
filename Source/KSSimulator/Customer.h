// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Customer.generated.h"

UCLASS()
class KSSIMULATOR_API ACustomer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomer();

protected:
	int32 NowStat = 0;
	int32 OrderNumber;
	int32 TableNum;

public:	

	FTimerHandle TimerHandle;
	class UCustomerMaker* CustomerMaker;

	void Hi(int32 InTableNum, UCustomerMaker* CM);
	void RingBell();
	void Order();
	void GetFood();
	void FinishFood();
	int32 GetStat();

	UPROPERTY()
	UMaterialInterface* MA;
	UPROPERTY()
	UMaterialInterface* MB;
	UPROPERTY()
	UMaterialInterface* MC;
	UPROPERTY()
	UMaterialInterface* MD;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};
