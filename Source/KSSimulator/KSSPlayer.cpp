// Fill out your copyright notice in the Description page of Project Settings.


#include "KSSPlayer.h"

// Sets default values
AKSSPlayer::AKSSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKSSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKSSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKSSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

