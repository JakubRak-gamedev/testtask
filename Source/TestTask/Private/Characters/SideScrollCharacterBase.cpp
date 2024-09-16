// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollCharacterBase.h"
#include "Components/CombatComponent.h"

ASideScrollCharacterBase::ASideScrollCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CombatComp = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
}


void ASideScrollCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASideScrollCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


