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

	Start = CreateDefaultSubobject<USceneComponent>("Start");
	Start->SetupAttachment(GetMesh(), "muzzle_01");

	End = CreateDefaultSubobject<USceneComponent>("End");
	End->SetupAttachment(GetMesh(), "WeaponTipSocket");

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

void ASideScrollMainCharacter::Attack(const FName& SideName,bool const bHeavyAttack)
{
	if (!bReadyToAttack) return;

	UAnimMontage* AttackMontage = CombatComp->GetAnimMontageFromProperties(SideName, bHeavyAttack);
	float BaseDamage = CombatComp->GetDamageFromMontage(AttackMontage) + FMath::RandRange(0, 4);

	
	if(!HasEnoughtStamina(BaseDamage / 2.f)) return;

	bIsAttacking = true;
	bReadyToAttack = false;

	
	float AnimLength = PlayAnimMontage(AttackMontage) + FMath::FRandRange(-0.5f, 0.5f);
	
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

	CombatComp->ReduceStamina(BaseDamage / 2);
}

bool ASideScrollMainCharacter::GetIsAttacking_Implementation()
{
	return bIsAttacking;
}

void ASideScrollMainCharacter::SetMaxHealth_Implementation(float NewHealth)
{
	CombatComp->SetMaxHealth(NewHealth);
}

void ASideScrollMainCharacter::SetMaxStamina_Implementation(float InStamina)
{
	CombatComp->SetMaxStamina(InStamina);
}

void ASideScrollMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	SplineFollowCamera = Cast<ASplineFollowCamera>(UGameplayStatics::GetActorOfClass(this, SplineFollowCameraClass));
	SplineRotateCamera = Cast<ASplineFollowCamera>(UGameplayStatics::GetActorOfClass(this, SplineRotateCameraClass));
}

void ASideScrollMainCharacter::AttackReset()
{
	bIsAttacking = false;
	bReadyToAttack = true;
}

bool ASideScrollMainCharacter::HasEnoughtStamina(const float Cost) const
{
	return CombatComp->HasEnoughStamina(Cost);
}

