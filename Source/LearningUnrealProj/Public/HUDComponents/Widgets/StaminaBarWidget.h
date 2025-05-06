// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "StaminaBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALPROJ_API UStaminaBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UStaminaBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	/* Takes percent of health left (CurrentStamina/MAX_STAMINA) */
	void UpdateStamina(float Value);

	/* Resets Health to 100% */
	void ResetStamina();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* StaminaBar;
};
