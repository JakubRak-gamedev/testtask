// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SideScrollCharacterBase.h"
#include "SideScrollEnemy.generated.h"

class UBehaviorTree;
class AEnemyAIController;
class UHealthBarComponent;
/**
 * 
 */
UCLASS()
class TESTTASK_API ASideScrollEnemy : public ASideScrollCharacterBase
{
	GENERATED_BODY()
public:
	ASideScrollEnemy();

	virtual void PossessedBy(AController* NewController);


	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category ="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AEnemyAIController> EnemyAIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
 	TObjectPtr<UHealthBarComponent> HealthBarComponent;
};
