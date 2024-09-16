// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SideScrollController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ASideScrollMainCharacter;
/**
 * 
 */
UCLASS()
class TESTTASK_API ASideScrollController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASideScrollController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	/*Variables*/
	TObjectPtr<ASideScrollMainCharacter> ControlledCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> Context;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	void Move(const FInputActionValue& Value);
	void Attack();
};
