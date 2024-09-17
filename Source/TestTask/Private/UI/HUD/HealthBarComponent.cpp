// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HealthBarComponent.h"
#include "UI/HUD/EnemyHealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UEnemyHealthBar>(GetUserWidgetObject());
	}

	if (HealthBarWidget && HealthBarWidget->ProgressBar_Main)
	{
		HealthBarWidget->ProgressBar_Main->SetPercent(Percent);
	}
}
