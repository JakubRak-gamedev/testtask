// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollMainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/SplineFollowCamera.h"
#include "Components/SplineComponent.h"

ASideScrollMainCharacter::ASideScrollMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(GetRootComponent());
}

void ASideScrollMainCharacter::Tick(float DeltaTime)
{
	if (SplineFollowCamera == nullptr) return;
	if (SplineRotateCamera == nullptr) return;

	const FVector CameraLocation = FollowCamera->GetComponentLocation();

	const FVector SplineLocationPoint = SplineFollowCamera->SplineComponent->FindLocationClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	const FVector SplineRotatePoint = SplineRotateCamera->SplineComponent->FindLocationClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);

	FVector Direction = SplineRotatePoint - SplineLocationPoint;

	FollowCamera->SetWorldLocation(UKismetMathLibrary::VInterpTo(CameraLocation, SplineLocationPoint, GetWorld()->GetDeltaSeconds(), 0.f));
	FollowCamera->SetWorldRotation(Direction.Rotation());
}

