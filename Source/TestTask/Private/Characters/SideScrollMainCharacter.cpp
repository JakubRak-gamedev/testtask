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
}

void ASideScrollMainCharacter::Attack()
{
	

	bIsAttacking = true;
	bReadyToAttack = false;

	float AnimLength = PlayAnimMontage(AttackMontage);
	
	const FVector SocketLocation = GetMesh()->GetSocketLocation(BladeSocket);
	const FVector Center = SocketLocation + GetActorForwardVector() * 100.f;
	
	GetWorldTimerManager().SetTimer(AttackTimerReset, this, &ASideScrollMainCharacter::AttackReset, AnimLength, true);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	TArray<AActor*> ActorsHit;

	UKismetSystemLibrary::SphereOverlapActors(this, Center, 100.f, ObjectTypes, AActor::StaticClass(), IgnoreActors, ActorsHit);

	for (AActor* HittedActor : ActorsHit)
	{
		UGameplayStatics::ApplyDamage(HittedActor, 20.f, Controller, this, UDamageType::StaticClass());
	}
}

float ASideScrollMainCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CombatComp->TakeDamage(Damage);

	if (CombatComp->GetHealth() <= 0.f)
	{
		// Die function
		GetMesh()->SetSimulatePhysics(true);

		GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);

		SetLifeSpan(5.f);
	}
	//Play HitReact Animation
	FString FloatAsString = FString::SanitizeFloat(CombatComp->GetHealth());

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("Damage Dealt: %s"), *FloatAsString));

	return Damage;
}

void ASideScrollMainCharacter::AttackReset()
{
	bIsAttacking = false;
	bReadyToAttack = true;
}

