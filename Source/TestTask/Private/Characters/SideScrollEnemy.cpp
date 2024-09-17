// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollEnemy.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void ASideScrollEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	EnemyAIController = Cast<AEnemyAIController>(NewController);
	EnemyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	EnemyAIController->RunBehaviorTree(BehaviorTree);
}
