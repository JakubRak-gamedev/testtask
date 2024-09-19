// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Stamina = MaxStamina;
}

void UCombatComponent::TakeDamage(float InDamage)
{
	Health = Health - InDamage;
}

void UCombatComponent::ReduceStamina(float ReduceAmount)
{
	Stamina = Stamina - ReduceAmount;
	Stamina = FMath::Clamp(Stamina, 0, MaxStamina);
}

UAnimMontage* UCombatComponent::GetAnimMontageFromProperties(const FName& SideName, bool bIsHeavy)
{
	for (const FUAttackProperties& Attack : Attacks)
	{
		if (Attack.SideName == SideName && Attack.IsHeavy == bIsHeavy)
			return Attack.AttackMontage;
	}

	return nullptr;
}

float UCombatComponent::GetDamageFromMontage(const UAnimMontage* Montage)
{
	for (const FUAttackProperties& Attack : Attacks)
	{
		if (Attack.AttackMontage == Montage)
			return Attack.BaseDamage;
	}

	return 0.f;
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float RegenRate = StaminaRegenRate;
	if(GetOwner()->GetVelocity().Size() > 0.f)
	{
		RegenRate =  -RegenRate;
	}
	
	Stamina = FMath::Clamp(Stamina + RegenRate * DeltaTime, 0.f, MaxStamina);
	
}

void UCombatComponent::SetMaxHealth(float InHealth)
{
	MaxHealth = InHealth;
}

void UCombatComponent::SetMaxStamina(float InStamina)
{
	MaxStamina = InStamina;
}

