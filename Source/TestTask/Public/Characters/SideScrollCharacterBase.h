// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SideScrollCharacterBase.generated.h"

class UCombatComponent;

UCLASS()
class TESTTASK_API ASideScrollCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ASideScrollCharacterBase();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Combat")
	TObjectPtr<UCombatComponent> CombatComp;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UAnimMontage> HitReact;
private:
	void Die();
	
};
