// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineFollowCamera.generated.h"

class USplineComponent;

UCLASS()
class TESTTASK_API ASplineFollowCamera : public AActor
{
	GENERATED_BODY()
	
public:	

	ASplineFollowCamera();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> SplineComponent;
protected:

	virtual void BeginPlay() override;

};
