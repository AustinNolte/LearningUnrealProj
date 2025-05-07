#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "Math/Vector4.h"
#include "Components/Image.h"


#include "HUDComponents/Widgets/HealthBarWidget.h"
#include "HUDComponents/Widgets/StaminaBarWidget.h" 
#include "HUDComponents/Widgets/AmmoAndWeaponDisplay.h"
#include "HUDComponents/Widgets/CrosshairComponent.h"

#include "Weapon.h"

#include "Components/CanvasPanel.h"
#include "MainCanvas.generated.h"

class UHealthBarWidget;
class UStaminaBarWidget;
class UAmmoAndWeaponDisplay;
class UCanvas;
class UImage;
class AWeapon;

UCLASS()
class LEARNINGUNREALPROJ_API UMainCanvas : public UUserWidget{

	GENERATED_BODY()

public:

	UMainCanvas(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MainCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHealthBarWidget* HealthBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UStaminaBarWidget* StaminaBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UAmmoAndWeaponDisplay* AmmoAndWeaponDisplay;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	UCrosshairComponent* CrosshairComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	UImage* AmmoAndWeaponDisplayBackground;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	UImage* HealthBarWidgetBackground;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	UImage* StaminaBarWidgetBackground;



public:

	/*------------- Health Bar Section ---------------- */
	

	/* Takes percent of health left (CurrentHealth/MAX_HEALTH) */
	void UpdateHealth(float Value);

	/* Resets Health to 100% */
	void ResetHealth(); 
	 

	/*------------- Stamina Bar Section ---------------- */

	/* Takes percent of Stamina left (CurrentStamina/MAX_STAMINA) */
	void UpdateStamina(float Value);

	/* Resets Stamina to 100% */
	void ResetStamina();

	/*------------- Ammo and Weapon Section ---------------- */
	
	/* Takes in currammo and MAX_AMMO in order to format a string to display current amount */
	void UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO);

	/* Resets Ammo to MAX_AMMO */
	void ResetAmmo(int32 MAX_AMMO);

	/* Changes weapon, this includes weapon icon and ammo count etc */
	void ChangeWeapon(AWeapon* NewWeapon);

	/* Toggles Visbility of Ammo and Weapon display */
	void ToggleAmmoAndWeaponDisplay();

	/*------------ Crosshair Section -------------------------*/
	
	/* Crosshair thickeness, in percent of screen space */
	void SetCrosshairThickness(float Value);

	/* Crosshair Gap, in percent of screen space */
	void SetCrosshairGap(float Value);

	/* CrosshairLen if crosshair type, in percent of screen space */
	void SetCrosshairLen(float Value);
	
	/* Corsshair Dot size if crosshair type is dot */
	void SetCrosshairDotSize(float Value);

	/* Color of crosshair in format of (R,G,B,A) */
	void SetCrosshairColor(FLinearColor Color);

	/* Set CrosshairType from enum of ECrossHairType */
	void SetCrosshairType(ECrossHairType CrosshairType);

	/* Set Reload Animation Percentage, Value should be 0-1 */
	void SetReloadPercentage(float Value);

	/* Toggle Visibility of reload circle */
	void ToggleReloadVisibility();
};
