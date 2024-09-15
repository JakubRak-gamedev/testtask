// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SplineFollowCamera.h"
#include "Components/SplineComponent.h"


ASplineFollowCamera::ASplineFollowCamera()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(GetRootComponent());
}


void ASplineFollowCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

