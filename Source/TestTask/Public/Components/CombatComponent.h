// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

USTRUCT(BlueprintType)
struct FUAttackProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseDamage = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SideName = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsHeavy = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();

	//Here we are mapping AnimMontages to amount of Base Damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attacks")
	TArray<FUAttackProperties> Attacks;
protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;
	float Health;

	UPROPERTY(EditAnywhere, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 60.f;
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenRate = 8.f;
public:
	
	//Getters & Setters
	void TakeDamage(float InDamage);

	void ReduceStamina(float ReduceAmount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetHealth() const  { return Health; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetStamina() const { return Stamina; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UAnimMontage* GetAnimMontageFromProperties(const FName& SideName, bool bIsHeavy);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetDamageFromMontage(const UAnimMontage* Montage);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasEnoughStamina(const float Cost) const {return Stamina > Cost;}

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void SetMaxHealth(float InHealth);

	void SetMaxStamina(float InStamina);
};
