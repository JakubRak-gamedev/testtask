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
	Lifes = MaxLifes;
}

void UCombatComponent::TakeDamage(float InDamage)
{
	Health = Health - InDamage;
	FMath::Clamp(Health, 0, MaxHealth);
	
	if(Health <= 0.f)
	{
		Lifes--;
		Health = MaxHealth;
	}
}

void UCombatComponent::ReduceStamina(float ReduceAmount)
{
	Stamina = Stamina - ReduceAmount;
	Stamina = FMath::Clamp(Stamina, 0, MaxStamina);
}

UAnimMontage* UCombatComponent::GetAnimMontageFromProperties(const FName& SideName, bool bIsHeavy)
{
	TArray<UAnimMontage*> AnimMontagesToChoose;
	for (const FUAttackProperties& Attack : Attacks)
	{
		if (Attack.SideName == SideName && Attack.IsHeavy == bIsHeavy)
		{
			AnimMontagesToChoose.Add(Attack.AttackMontage);
		}
	}

	if(AnimMontagesToChoose.Num() > 0)
		return AnimMontagesToChoose[FMath::RandRange(0, AnimMontagesToChoose.Num() - 1)];
	
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

	//stamina regen logic

	/* if we are moving then make regen to negative
	 *
	 * instead we could make it a variable and give it uproperty to edit it from editor
	 */
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

