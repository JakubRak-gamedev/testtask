// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "SideScrollCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHitReactChanged, bool)

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_NonCombat UMETA(DisplayName = "NonCombat"),
	ECS_InCombat UMETA(DisplayName = "InCombat"),

	ECS_MAX UMETA(DisplayName = "DefaultMAX")
};

class UCombatComponent;
class UBoxComponent;

UCLASS()
class TESTTASK_API ASideScrollCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:

	ASideScrollCharacterBase();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Combat")
	TObjectPtr<UCombatComponent> CombatComp;

	/*
	 * Because we are Enemy and MainCharacter class are inherited from BaseClass, that means all of them share the same TakeDamage function
	 */
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UAnimMontage> HitReact;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	ECombatState CombatState = ECombatState::ECS_NonCombat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UBoxComponent> WeaponBox;

	FOnHitReactChanged OnHitReactChangedSignature;
	bool bHitReacting = false;
	void ResetHitReact();

	UPROPERTY(BlueprintReadWrite)
	bool bReadyToAttack = true;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking = false;

private:
	void Die();

	FTimerHandle HitReactTimer;
public:
	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool GetReadyToAttack() const { return bReadyToAttack; }
};
