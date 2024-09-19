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

	void Attack(const FName& SideName, bool const bHeavyAttack);

	/*CombatInterface Functions*/
	virtual bool GetIsAttacking_Implementation() override;

	virtual void SetMaxHealth_Implementation(float NewHealth) override;

	virtual void SetMaxStamina_Implementation(float InStamina) override;
	/*END*/
protected:

	virtual void BeginPlay();

private:

	UPROPERTY(BlueprintReadWrite, Category = "CameraSettings", meta = (AllowPrivateAccess="true"))
	TObjectPtr<ASplineFollowCamera> SplineFollowCamera;

	UPROPERTY(BlueprintReadWrite, Category = "CameraSettings", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASplineFollowCamera>	SplineRotateCamera;

	UPROPERTY(EditDefaultsOnly , Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FName BladeSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Start;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> End;

	FTimerHandle AttackTimerReset;
	void AttackReset();
	
	float MovementOffsetYaw = 0.f;
public:
	/*GETTERS & SETTERS*/
	
	FORCEINLINE void SetOffsetYaw(float InValue) {	MovementOffsetYaw = InValue;}
	FORCEINLINE float GetOffSetYaw() const { return MovementOffsetYaw; }

	bool HasEnoughStamina(const float Cost) const;
};
