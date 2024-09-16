// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollCharacterBase.h"
#include "Components/CombatComponent.h"
#include "Kismet/GameplayStatics.h"

ASideScrollCharacterBase::ASideScrollCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CombatComp = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
}


float ASideScrollCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ASideScrollCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASideScrollCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


