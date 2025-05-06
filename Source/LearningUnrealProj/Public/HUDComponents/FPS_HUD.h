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

	/* Takes percent of health left (CurrentHealth/MAX_HEALTH) */
	void UpdateStamina(float Value);

	/* Resets Health to 100% */
	void ResetStamina();

private:
	UMainCanvas* MainGameCanvas;
};
