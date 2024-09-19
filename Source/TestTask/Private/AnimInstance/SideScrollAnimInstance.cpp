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
	
}

void USideScrollAnimInstance::NativeInitializeAnimation()
{
	SideScrollCharacter = Cast<ASideScrollMainCharacter>(TryGetPawnOwner());
}

