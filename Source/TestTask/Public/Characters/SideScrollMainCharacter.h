// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SideScrollCharacterBase.h"
#include "SideScrollMainCharacter.generated.h"

class ASplineFollowCamera;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class TESTTASK_API ASideScrollMainCharacter : public ASideScrollCharacterBase
{
	GENERATED_BODY()
	
public:
	ASideScrollMainCharacter();

	virtual void Tick(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings")
	TSubclassOf<ASplineFollowCamera> SplineFollowCameraClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings")
	TSubclassOf<ASplineFollowCamera> SplineRotateCameraClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CameraSettings")
	TObjectPtr<UCameraComponent> FollowCamera;
protected:
	

private:

	UPROPERTY(BlueprintReadWrite, Category = "CameraSettings", meta = (AllowPrivateAccess="true"))
	TObjectPtr<ASplineFollowCamera> SplineFollowCamera;

	UPROPERTY(BlueprintReadWrite, Category = "CameraSettings", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASplineFollowCamera>	SplineRotateCamera;


public:
	/*GETTERS & SETTERS*/
	
};
