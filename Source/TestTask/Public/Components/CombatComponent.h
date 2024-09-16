// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;
	float Health;

	UPROPERTY(EditAnywhere, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxStamina = 60.f;
	float Stamina;

public:
	
	//Getters & Setters
	void TakeDamage(float InDamage);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetHealth() { return Health; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetMaxStamina() { return MaxStamina; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetStamina() { return Stamina; }
		
};
