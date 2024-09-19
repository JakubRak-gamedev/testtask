// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollEnemy.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UI/HUD/HealthBarComponent.h"
#include "Components/CombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASideScrollEnemy::ASideScrollEnemy()
{
	HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>("HealthBar");
	HealthBarComponent->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

void ASideScrollEnemy::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle AttackRefresh;
	GetWorldTimerManager().SetTimer(AttackRefresh, this, &ASideScrollEnemy::AttackRefresh, 2.f, true);
	
	if (HealthBarComponent)
	{
		HealthBarComponent->SetHealthPercent(CombatComp->GetHealth() / CombatComp->GetMaxHealth());
	}

	OnHitReactChangedSignature.AddLambda(
		[this](bool bInReacting)
		{
			EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bInReacting);
		});
}

void ASideScrollEnemy::AttackRefresh()
{
	EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsAttacking"), bIsAttacking);
}

void ASideScrollEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	EnemyAIController = Cast<AEnemyAIController>(NewController);
	EnemyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	EnemyAIController->RunBehaviorTree(BehaviorTree);
	EnemyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
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

bool ASideScrollEnemy::GetIsAttacking_Implementation()
{
	return bIsAttacking;
}


