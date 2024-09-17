// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SideScrollController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
	if (!ControlledCharacter->bHasStamina()) return;

	const FVector2D ValueVector = Value.Get<FVector2D>();
	FRotator CameraRotation = ControlledCharacter->FollowCamera->GetComponentRotation();
	FRotator YawRotation(0, CameraRotation.Yaw, 0);  // Ignore pitch and roll for movement
	
	// Get forward vector relative to the camera's yaw rotation
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	ControlledCharacter->AddMovementInput(ForwardDirection, ValueVector.X);
	ControlledCharacter->AddMovementInput(RightDirection, ValueVector.Y);
   
	
	FVector CameraForward = CameraRotation.Vector();
	CameraForward.Z = 0;
	CameraForward.Normalize();
	FVector CameraRight = FVector::CrossProduct(FVector::UpVector, CameraForward);
	CameraRight.Normalize();
	FVector MovementDirection = CameraRight * ValueVector.Y;

	if (ControlledCharacter->GetCombatState() == ECombatState::ECS_InCombat)
	{
		ControlledCharacter->SetActorRotation(CameraRight.Rotation());
	}
	else
	{
		//ControlledCharacter->SetActorRotation(MovementDirection.Rotation());

		ControlledCharacter->SetActorRotation(CameraRight.Rotation());
	}
	
	FRotator AimRotation = CameraRight.Rotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ControlledCharacter->GetVelocity());

	// Calculate the yaw difference between aim and movement
	float YawDifference = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

	ControlledCharacter->SetOffsetYaw(YawDifference);
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

