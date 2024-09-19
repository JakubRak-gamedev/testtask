// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

AEnemyAIController::AEnemyAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	PawnSensingComponent->SightRadius = 1000.f;
	PawnSensingComponent->SetPeripheralVisionAngle(45.f);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

