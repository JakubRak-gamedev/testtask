// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SideScrollHUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API ASideScrollHUD : public AHUD
{
	GENERATED_BODY()
	

public:

	UPROPERTY()
	TObjectPtr<UUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
};
