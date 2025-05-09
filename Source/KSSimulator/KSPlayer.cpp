// Fill out your copyright notice in the Description page of Project Settings.


#include "KSPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Customer.h"

// Sets default values
// Sets default values
AKSPlayer::AKSPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKSPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		if (LocalPlayer)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

			if (Subsystem)
			{
				Subsystem->AddMappingContext(IMC_Player, 0);
			}
		}
	}
}

// Called every frame
void AKSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FVector WorldLocation, WorldDirection;
		if (PC->DeprojectScreenPositionToWorld(
			1920 / 2.0f, 1080 / 2.0f,
			WorldLocation, WorldDirection))
		{
			FVector Start;
			FRotator ViewRot;

			PC->GetPlayerViewPoint(Start, ViewRot);
			FVector ForwardVector = ViewRot.Vector();
			FVector End = Start + (ForwardVector * 250.0f);

			FHitResult HitResult;

			FCollisionQueryParams TraceParams;
			TraceParams.AddIgnoredActor(this);

			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Start,
				End,
				ECC_Visibility,
				TraceParams
			);

			bool IsRed = false;
			if (bHit) //Actor Tag Setting first
			{
				if (HitResult.GetActor()->Tags.Contains("In"))
				{
					if (RayStatus == 0)
					{
						IsRed = true;
					}
				}
				else if (HitResult.GetActor()->Tags.Contains("Fo"))
				{
					if (RayStatus == 0 || RayStatus == 1)
					{
						IsRed = true;
					}
				}
				else if (HitResult.GetActor()->Tags.Contains("Cu"))
				{
					ACustomer* CC = Cast<ACustomer>(HitResult.GetActor());
					int32 GG = CC->GetStat();
					if (RayStatus == 0 && GG == 1 || RayStatus == 2 && GG == 2)
					{
						IsRed = true;
					}
				}
			}
			if (IsRed) MyHUD->Color = FLinearColor::Red;
			else MyHUD->Color = FLinearColor::White;
		}
	}
}

void AKSPlayer::SetPlayerHUD(APlayerHUD* HUD)
{
	MyHUD = HUD;
}

// Called to bind functionality to input
void AKSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		BindInputActions(EnhancedInputComponent);
	}
}

void AKSPlayer::BindInputActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (IA_Move)
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AKSPlayer::OnInputMove);
	}
	if (IA_Camera)
	{
		EnhancedInputComponent->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &AKSPlayer::OnCameraMove);
	}
	if (IA_Click)
	{
		EnhancedInputComponent->BindAction(IA_Click, ETriggerEvent::Started, this, &AKSPlayer::OnClick);
	}
}

void AKSPlayer::OnInputMove(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	FVector ForwardDirection = GetActorForwardVector() * MoveVector.Y;
	FVector RightDirection = GetActorRightVector() * MoveVector.X;
	FVector MoveDirection = ForwardDirection + RightDirection;

	if (MoveDirection.SizeSquared() > 0.0f)
	{
		AddMovementInput(MoveDirection.GetSafeNormal());
	}
}

void AKSPlayer::OnCameraMove(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	AddControllerYawInput(MoveVector.X);
	AddControllerPitchInput(-MoveVector.Y);
	
}

void AKSPlayer::OnClick(const FInputActionValue& Value)
{
	float F = Value.Get<float>();

	if (F == 1.f) //l
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			FVector WorldLocation, WorldDirection;
			if (PC->DeprojectScreenPositionToWorld(
				1920 / 2.0f, 1080 / 2.0f,
				WorldLocation, WorldDirection))
			{
				FVector Start;
				FRotator ViewRot;

				PC->GetPlayerViewPoint(Start, ViewRot);
				FVector ForwardVector = ViewRot.Vector();
				FVector End = Start + (ForwardVector * 250.0f);

				FHitResult HitResult;

				FCollisionQueryParams TraceParams;
				TraceParams.AddIgnoredActor(this);

				bool bHit = GetWorld()->LineTraceSingleByChannel(
					HitResult,
					Start,
					End,
					ECC_Visibility,
					TraceParams
				);

				if (bHit) //Actor Tag Setting first
				{
					if (HitResult.GetActor()->Tags.Contains("In"))
					{
						if (RayStatus == 0)
						{
							RayStatus = 1;
						}
					}
					if (HitResult.GetActor()->Tags.Contains("Cu"))
					{
						ACustomer* CC = Cast<ACustomer>(HitResult.GetActor());
						int32 GG = CC->GetStat();
						if (RayStatus == 0)
						{
							if (GG == 1) CC->Order();
						}
					}
				}
			}
		}
	}
	else if (F == -1.f) //r
	{
		RayStatus = 0;
		//add trash
	}
}

