// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SideScrollController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Characters/SideScrollMainCharacter.h"

ASideScrollController::ASideScrollController()
{
}

void ASideScrollController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(Context, 0);

	ControlledCharacter = GetPawn<ASideScrollMainCharacter>();
}

void ASideScrollController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASideScrollController::Move);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ASideScrollController::Attack);
}

void ASideScrollController::Move(const FInputActionValue& Value)
{
	if (ControlledCharacter == nullptr) return;
	if (ControlledCharacter->GetIsAttacking()) return;

	const FVector2D ValueVector = Value.Get<FVector2D>();
	FRotator CameraRotation = ControlledCharacter->FollowCamera->GetComponentRotation();
	FRotator YawRotation(0, CameraRotation.Yaw, 0);  // Ignore pitch and roll for movement
	
	// Get forward vector relative to the camera's yaw rotation
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	ControlledCharacter->AddMovementInput(ForwardDirection, ValueVector.X);
	ControlledCharacter->AddMovementInput(RightDirection, ValueVector.Y);
   

}

void ASideScrollController::Attack()
{
	if (ControlledCharacter == nullptr) return;

	ControlledCharacter->Attack();

}
