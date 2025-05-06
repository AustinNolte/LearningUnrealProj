#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "MainCanvas.h"

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

private:
	UMainCanvas* MainGameCanvas;
};
