// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollCharacterBase.h"
#include "Components/CombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

ASideScrollCharacterBase::ASideScrollCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CombatComp = CreateDefaultSubobject<UCombatComponent>("CombatComponent");

	GetCharacterMovement()->MaxWalkSpeed = 350.f;
}


float ASideScrollCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Here we are substracting Damage from our current Health
	CombatComp->TakeDamage(Damage);

	PlayAnimMontage(HitReact);

	if (CombatComp->GetHealth() <= 0.f)
	{
		Die();
	}
	
	return Damage;
}

void ASideScrollCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASideScrollCharacterBase::Die()
{
	//Enabling Ragdoll
	GetMesh()->SetSimulatePhysics(true);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);

	SetLifeSpan(5.f);
}

void ASideScrollCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


