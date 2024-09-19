// Fill out your copyright notice in the Description page of Project Settings.


#include "CheatManager/SideScrollCheatManager.h"

#include "Characters/SideScrollMainCharacter.h"
#include "Kismet/GameplayStatics.h"

void USideScrollCheatManager::AddMaxHealth(float NewHealth)
{
	ASideScrollMainCharacter* Character = Cast<ASideScrollMainCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	ICombatInterface::Execute_SetMaxHealth(Character, NewHealth);

	GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Red, FString("Health CheatActivated!"));
}

void USideScrollCheatManager::AddMaxStamina(float NewStamina)
{
	ASideScrollMainCharacter* Character = Cast<ASideScrollMainCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	ICombatInterface::Execute_SetMaxStamina(Character, NewStamina);

	GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Red, FString("Stamina CheatActivated!"));
}
