// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include <HUDComponents/Widgets/CrosshairComponent.h>
#include "PlayerUserSettings.generated.h"
UCLASS()
class LEARNINGUNREALPROJ_API UPlayerUserSettings : public UGameUserSettings{

	GENERATED_BODY()
	
public:

	/* Crosshair gap*/
	UPROPERTY(config,EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float CrosshairGap = 1;

	/* Crosshair len */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float CrosshairLen = 1;

	/* Crosshair Thickness*/
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float CrosshairThickness = 1;

	/* Dot Size if crosshair type is dot */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.2", ClampMax = "5.0"))
	float CrosshairDotSize = 1;

	/* Crosshair color, Vector of (R,G,B,A) with A being Alpha (Opacity), Default white */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "255.0"))
	FVector4 RGBColor = FVector4(255.0f, 255.0f, 255.0f, 255.0f);

	/* Crosshair Type cross by default */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite)
	ECrossHairType Type = ECrossHairType::Cross;

	/* sens of player */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite)
	float Sensitivity;

	/* game sound */
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite)
	float OverallSound;

public:

	UFUNCTION(Blueprintcallable)
	FORCEINLINE float GetCrosshairGap() { return CrosshairGap; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCrosshairLen() { return CrosshairLen; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCrosshairThickness() { return CrosshairThickness; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCrosshairDotSize() { return CrosshairDotSize; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector4 GetRGBColor() { return RGBColor; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE uint8 GetCrosshairType() { return (uint8)Type; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetSensitivity() { return Sensitivity; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetOverallSound() { return OverallSound; }

	UFUNCTION(BlueprintCallable)
	void SetCrosshairGap(float Value);

	UFUNCTION(BlueprintCallable)
	void SetCrosshairLen(float Value);

	UFUNCTION(BlueprintCallable)
	void SetCrosshairThickness(float Value);

	UFUNCTION(BlueprintCallable)
	void SetCrosshairDotSize(float Value);

	UFUNCTION(BlueprintCallable)
	void SetRGBColor(FVector4 Value);

	UFUNCTION(BlueprintCallable)
	void SetCrosshairType(uint8 Value);

	UFUNCTION(BlueprintCallable)
	void SetSensitivity(float Value);

	UFUNCTION(BlueprintCallable)
	void SetSound(float Value);

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;

	UFUNCTION(BlueprintCallable)
	static UPlayerUserSettings* GetPlayerUserSettings();

	



};
