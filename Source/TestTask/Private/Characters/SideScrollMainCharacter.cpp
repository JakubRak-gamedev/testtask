// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SideScrollMainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/SplineFollowCamera.h"
#include "Components/SplineComponent.h"
#include "Components/CombatComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ASideScrollMainCharacter::ASideScrollMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(GetRootComponent());
}

void ASideScrollMainCharacter::Tick(float DeltaTime)
{
	if (SplineFollowCamera == nullptr) return;
	if (SplineRotateCamera == nullptr) return;

	const FVector CameraLocation = FollowCamera->GetComponentLocation();

	const FVector SplineLocationPoint = SplineFollowCamera->SplineComponent->FindLocationClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	const FVector SplineRotatePoint = SplineRotateCamera->SplineComponent->FindLocationClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);

	FVector Direction = SplineRotatePoint - SplineLocationPoint;

	FollowCamera->SetWorldLocation(UKismetMathLibrary::VInterpTo(CameraLocation, SplineLocationPoint, GetWorld()->GetDeltaSeconds(), 0.f));
	FollowCamera->SetWorldRotation(Direction.Rotation());

	if (!bIsAttacking && bReadyToAttack)
	{
		//easy way to add stamina regen functionallity, but i'd personally change it on release because its confusing
		if (GetVelocity().Size() < 150.f)
		{
			CombatComp->ReduceStamina(-0.1f);
		}
		if (GetVelocity().Size() <= 1.f)
		{
			CombatComp->ReduceStamina(-1.f);
		}
		
	}
}

void ASideScrollMainCharacter::Attack(const FName& SideName,bool const bHeavyAttack)
{
	if (CombatComp->GetStamina() - /*ReduceAmount*/ 10.f < 0.f && !bReadyToAttack) return;

	bIsAttacking = true;
	bReadyToAttack = false;

	UAnimMontage* AttackMontage = CombatComp->GetAnimMontageFromProperties(SideName, bHeavyAttack);
	float BaseDamage = CombatComp->GetDamageFromMontage(AttackMontage) + FMath::RandRange(0, 15);
	float AnimLength = PlayAnimMontage(AttackMontage);
	
	const FVector SocketLocation = GetMesh()->GetSocketLocation(BladeSocket);
	const FVector Center = SocketLocation + GetActorForwardVector() * 100.f;
	
	GetWorldTimerManager().SetTimer(AttackTimerReset, this, &ASideScrollMainCharacter::AttackReset, AnimLength, false);

	//defining what object types we are looking for
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<AActor*> ActorsHitted;
	UKismetSystemLibrary::SphereOverlapActors(this, Center, 100.f, ObjectTypes, AActor::StaticClass(), IgnoreActors, ActorsHitted);

	for (AActor* HittedActor : ActorsHitted)
	{
		UGameplayStatics::ApplyDamage(HittedActor, BaseDamage, Controller, this, UDamageType::StaticClass());
	}

	CombatComp->ReduceStamina(BaseDamage - 8.f);
}

void ASideScrollMainCharacter::AttackReset()
{
	bIsAttacking = false;
	bReadyToAttack = true;

	FString StaminaStr = FString::SanitizeFloat(CombatComp->GetStamina());
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Stamina: %s"), *StaminaStr));
}

