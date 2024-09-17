// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollEnemy.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UI/HUD/HealthBarComponent.h"
#include "Components/CombatComponent.h"

ASideScrollEnemy::ASideScrollEnemy()
{
	HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>("HealthBar");
	HealthBarComponent->SetupAttachment(GetRootComponent());
}

void ASideScrollEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarComponent)
	{
		HealthBarComponent->SetHealthPercent(CombatComp->GetHealth() / CombatComp->GetMaxHealth());
	}
}

void ASideScrollEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	EnemyAIController = Cast<AEnemyAIController>(NewController);
	EnemyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	EnemyAIController->RunBehaviorTree(BehaviorTree);
}

float ASideScrollEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if(HealthBarComponent)
	{
		HealthBarComponent->SetHealthPercent(CombatComp->GetHealthPercent());
		
	}
	
	return 0.f;
}


