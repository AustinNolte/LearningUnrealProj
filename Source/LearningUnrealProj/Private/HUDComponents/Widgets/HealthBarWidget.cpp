// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDComponents/Widgets/HealthBarWidget.h"

UHealthBarWidget::UHealthBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	
}

void UHealthBarWidget::NativeConstruct(){
	Super::NativeConstruct();

}

void UHealthBarWidget::UpdateHealth(float Value){
	
	if (HealthBar) {
		HealthBar->SetPercent(Value);
	}
}

void UHealthBarWidget::ResetHealth(){
	
	if (HealthBar) {
		HealthBar->SetPercent(100.0f);
	}
}
