// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/SideScrollAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/SideScrollMainCharacter.h"
#include "Camera/CameraComponent.h"

void USideScrollAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (SideScrollCharacter == nullptr)
	{
		SideScrollCharacter = Cast<ASideScrollMainCharacter>(TryGetPawnOwner());
	}

	if (!SideScrollCharacter) return;
	
	FVector Velocity = SideScrollCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();

	bIsAccelerating = SideScrollCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
	
	MovementOffset = SideScrollCharacter->GetOffSetYaw();

	bIsInCombat = SideScrollCharacter->GetCombatState() == ECombatState::ECS_InCombat;

	GEngine->AddOnScreenDebugMessage(1, -1, FColor::Blue, FString::Printf(TEXT("Offset: %f"), MovementOffset));
	//TurnInPlace();
}

void USideScrollAnimInstance::NativeInitializeAnimation()
{
	SideScrollCharacter = Cast<ASideScrollMainCharacter>(TryGetPawnOwner());
}

void USideScrollAnimInstance::TurnInPlace()
{
	if (SideScrollCharacter == nullptr) return;

	if (Speed > 0)
	{

	}
	else
	{
		CharacterYawLastFrame = CharacterYaw;
		CharacterYaw = SideScrollCharacter->GetActorRotation().Yaw;

		const float YawDelta = CharacterYaw - CharacterYawLastFrame;

		RootYawOffSet -= YawDelta;


		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, -1, FColor::Blue, FString::Printf(TEXT("CharacterYaw: %f"), CharacterYaw));

			GEngine->AddOnScreenDebugMessage(2, -1, FColor::Green, FString::Printf(TEXT("CharacterYaw: %f"), RootYawOffSet));
		}
	}
}
