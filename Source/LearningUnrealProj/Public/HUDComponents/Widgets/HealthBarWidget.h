// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALPROJ_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UHealthBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	/* Takes percent of health left (CurrentHealth/MAX_HEALTH) */
	void UpdateHealth(float Value);
	
	/* Resets Health to 100% */
	void ResetHealth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;
	
};
