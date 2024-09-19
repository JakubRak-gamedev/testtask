// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class UPawnSensingComponent;
/**
 * 
 */
UCLASS()
class TESTTASK_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent;
};
