// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SideScrollHUD.h"
#include "Blueprint/UserWidget.h"

void ASideScrollHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	Widget->AddToViewport();
}
