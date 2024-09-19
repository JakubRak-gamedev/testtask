// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "SideScrollCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API USideScrollCheatManager : public UCheatManager
{
	GENERATED_BODY()

	UFUNCTION(Exec, Category = "Cheats")
	void AddMaxHealth(float NewHealth);

	UFUNCTION(Exec, Category = "Cheats")
	void AddMaxStamina(float NewStamina);
};
