// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SideScrollCharacterBase.generated.h"

class UCombatComponent;

UCLASS()
class TESTTASK_API ASideScrollCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ASideScrollCharacterBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Combat")
	TObjectPtr<UCombatComponent> CombatComp;
protected:

	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
};
