// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeInOutWidget.h"

void UFadeInOutWidget::FadeIn()
{
    if (FadeInAnimation)
    {
        PlayAnimation(FadeInAnimation);
    }
}

void UFadeInOutWidget::FadeOut()
{
    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation);
    }
}