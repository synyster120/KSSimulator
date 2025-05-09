// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "PlayerHUD.h"
#include "KSPlayer.generated.h"

UCLASS()
class KSSIMULATOR_API AKSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKSPlayer();

private:
	void BindInputActions(class UEnhancedInputComponent* EnhancedInputComponent);
	void OnInputMove(const FInputActionValue& Value);
	void OnCameraMove(const FInputActionValue& Value);
	void OnClick(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Input")
	class UInputMappingContext* IMC_Player;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Input")
	class UInputAction* IA_Camera;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Input")
	class UInputAction* IA_Click;

	APlayerHUD* MyHUD;
	int32 RayStatus = 0; // nothing, ingredient, food

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetPlayerHUD(APlayerHUD* HUD);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
