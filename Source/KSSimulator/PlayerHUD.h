// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class KSSIMULATOR_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void DrawHUD() override;

public:
	bool IfDraw = true;
	FLinearColor Color = FLinearColor::White;

};
