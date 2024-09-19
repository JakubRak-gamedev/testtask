// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollCharacterBase.h"
#include "Components/CombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"



ASideScrollCharacterBase::ASideScrollCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CombatComp = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	WeaponBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	WeaponBox->SetupAttachment(GetMesh(), FName("BladeSocket"));

	GetCharacterMovement()->MaxWalkSpeed = 350.f;

}


float ASideScrollCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Here we are subtracting Damage from our current Health
	CombatComp->TakeDamage(Damage);

	float HitReactLength = PlayAnimMontage(HitReact);
	bHitReacting = true;
	OnHitReactChangedSignature.Broadcast(bHitReacting);
	
	GetWorldTimerManager().SetTimer(HitReactTimer, this, &ASideScrollCharacterBase::ResetHitReact, HitReactLength, false);
	
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

void ASideScrollCharacterBase::ResetHitReact()
{
	bHitReacting = false;
	OnHitReactChangedSignature.Broadcast(bHitReacting);
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


