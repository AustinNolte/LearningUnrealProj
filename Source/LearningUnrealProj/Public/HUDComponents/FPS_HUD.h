#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "MainCanvas.h"

// for enum type
#include "HUDComponents/Widgets/CrosshairComponent.h"

#include "FPS_HUD.generated.h"

class UMainCanvas;

UCLASS()
class LEARNINGUNREALPROJ_API AFPS_HUD : public AHUD{
	GENERATED_BODY()
	
public:

	AFPS_HUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainCanvas> MainGameUIClass;

	/* Crosshair gap*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin ="0.0", ClampMax = "10.0"))
	float CrosshairGap = 1;

	/* Crosshair len */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float CrosshairLen = 1;

	/* Crosshair Thickness*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float CrosshairThickness = 1;

	/* Crosshair color, Vector of (R,G,B,A) with A being Alpha (Opacity), Default white */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "255.0"))
	FVector4 RGBColor = FVector4(255.0f, 255.0f, 255.0f, 255.0f); 

	/* Crosshair Type cross by default */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ECrossHairType Type = ECrossHairType::Cross;


	/*------------- Health Bar Section ---------------- */

	/* Takes percent of health left (CurrentHealth/MAX_HEALTH) */
	void UpdateHealth(float Value);

	/* Resets Health to 100% */
	void ResetHealth();

	/*------------- Stamina Bar Section ---------------- */

	/* Takes percent of health left (CurrentHealth/MAX_HEALTH) */
	void UpdateStamina(float Value);

	/* Resets Health to 100% */
	void ResetStamina();

	/*------------- Ammo and Display Section ---------------- */

	/* Takes in currammo and MAX_AMMO in order to format a string to display current amount */
	void UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO);

	/* Resets Ammo to MAX_AMMO */
	void ResetAmmo(int32 MAX_AMMO);

	/* Changes weapon, this includes weapon icon and ammo count etc */
	void ChangeWeapon(AWeapon* NewWeapon);

	/*------------- Crosshair Section ---------------- */
	
	void DrawCrosshair();
	
	void DrawCircleCrosshair();
	
	void DrawDotCrosshair();

	/*------------ Crosshair Section -------------------------*/

	/* Crosshair thickeness, in percent of screen space */
	void SetCrosshairThickness(float Value);

	/* Crosshair Gap, in percent of screen space */
	void SetCrosshairGap(float Value);

	/* CrosshairLen if crosshair type, in percent of screen space */
	void SetCrosshairLen(float Value);

	/* Color of crosshair in format of (R,G,B,A) */
	void SetCrosshairColor(FLinearColor Color);

	/* Set CrosshairType from enum of ECrossHairType */
	void SetCrosshairType(ECrossHairType CrosshairType);

private:
	UMainCanvas* MainGameCanvas;
};
