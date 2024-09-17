// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SideScrollCharacterBase.h"
#include "SideScrollEnemy.generated.h"

class UBehaviorTree;
class AEnemyAIController;
/**
 * 
 */
UCLASS()
class TESTTASK_API ASideScrollEnemy : public ASideScrollCharacterBase
{
	GENERATED_BODY()
public:
	virtual void PossessedBy(AController* NewController);

protected:
	UPROPERTY(EditDefaultsOnly, Category ="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AEnemyAIController> EnemyAIController;
};
