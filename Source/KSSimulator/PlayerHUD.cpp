// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void APlayerHUD::DrawHUD()
{
    Super::DrawHUD();

    if (Canvas && IfDraw)
    {
        const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        const float Radius = 5.0f;

        DrawRect(Color, Center.X - Radius * 0.5f, Center.Y - Radius * 0.5f, Radius, Radius);
    }
}