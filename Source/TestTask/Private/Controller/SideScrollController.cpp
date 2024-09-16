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
	EnhancedInputComponent->BindAction(RightAttackAction, ETriggerEvent::Started, this, &ASideScrollController::RightLightAttack);
	EnhancedInputComponent->BindAction(RightAttackAction, ETriggerEvent::Started, this, &ASideScrollController::RightHeavyAttack);
	EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ASideScrollController::ShiftKeyPressed);
	EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ASideScrollController::ShiftKeyReleased);
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

void ASideScrollController::RightLightAttack()
{
	if (bShiftKeyDown == true) return;
	if (ControlledCharacter == nullptr) return;

	ControlledCharacter->Attack(FName("Right"), false);
}

void ASideScrollController::RightHeavyAttack()
{
	if (bShiftKeyDown == false) return;
	if (ControlledCharacter == nullptr) return;

	ControlledCharacter->Attack(FName("Right"), true);
}

void ASideScrollController::LeftLightAttack()
{
	if (bShiftKeyDown == true) return;
	if (ControlledCharacter == nullptr) return;

	ControlledCharacter->Attack(FName("Left"), false);
}

void ASideScrollController::LeftHeavyAttack()
{
	if (bShiftKeyDown == false) return;
	if (ControlledCharacter == nullptr) return;

	ControlledCharacter->Attack(FName("Left"), true);
}

void ASideScrollController::ShiftKeyPressed()
{
	bShiftKeyDown = true;
}

void ASideScrollController::ShiftKeyReleased()
{
	bShiftKeyDown = false;
}

