#include "HUDComponents/FPS_HUD.h"

AFPS_HUD::AFPS_HUD(){}



void AFPS_HUD::DrawHUD(){
	Super::DrawHUD();
}

void AFPS_HUD::BeginPlay(){
	Super::BeginPlay();

	if (MainGameUIClass && GetWorld()) {
		
		MainGameCanvas = CreateWidget<UMainCanvas>(GetWorld(), MainGameUIClass);
		if (MainGameCanvas) {
			MainGameCanvas->AddToViewport();

			// from manual tweaking, This is too allow for ease of setting. Simpler to image crosshair thickness of 10 rather than .1
			CrosshairThickness *= 0.005;
			SetCrosshairThickness(CrosshairThickness);
		
			// same as thickness
			CrosshairGap *= 0.1;
			SetCrosshairGap(CrosshairGap);
			
			// same as thickness
			CrosshairLen *= 0.05;
			SetCrosshairLen(CrosshairLen);

			CrosshairDotSize *= 0.05;
			SetCrosshairDotSize(CrosshairDotSize);
			
			SetCrosshairColor(RGBColor);
			
			SetCrosshairType(Type);
		}
	}
}

void AFPS_HUD::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
}

/*------------- Health Bar Section ---------------- */

void AFPS_HUD::UpdateHealth(float Value){
	if (MainGameCanvas) {
		MainGameCanvas->UpdateHealth(Value);
	}
}

void AFPS_HUD::ResetHealth() {
	if (MainGameCanvas) {
		MainGameCanvas->ResetHealth();
	}
}

/*------------- Stamina Bar Section ---------------- */


void AFPS_HUD::UpdateStamina(float Value) {
	if (MainGameCanvas) {
		MainGameCanvas->UpdateStamina(Value);
	}
}

void AFPS_HUD::ResetStamina() {
	if (MainGameCanvas) {
		MainGameCanvas->ResetStamina();
	}
}

/*------------- Ammo and Display Section ---------------- */

void AFPS_HUD::UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO) {
	if (MainGameCanvas) {
		MainGameCanvas->UpdateAmmo(CurrAmmo, MAX_AMMO);
	}
}

void AFPS_HUD::ResetAmmo(int32 MAX_AMMO) {
	if (MainGameCanvas) {
		MainGameCanvas->ResetAmmo(MAX_AMMO);
	}
}

void AFPS_HUD::ChangeWeapon(AWeapon* NewWeapon) {
	if (MainGameCanvas) {
		MainGameCanvas->ChangeWeapon(NewWeapon);
	}
}

void AFPS_HUD::ToggleAmmoAndWeaponDisplay() {
	if (MainGameCanvas) {
		MainGameCanvas->ToggleAmmoAndWeaponDisplay();
	}
}

/*------------ Crosshair Section -------------------------*/

void AFPS_HUD::SetCrosshairThickness(float Value) {
	if (MainGameCanvas) {
		MainGameCanvas->SetCrosshairThickness(Value);
	}
}

void AFPS_HUD::SetCrosshairGap(float Value) {
	if (MainGameCanvas) {
		MainGameCanvas->SetCrosshairGap(Value);
	}
}

void AFPS_HUD::SetCrosshairLen(float Value) {
	if (MainGameCanvas) {
		MainGameCanvas->SetCrosshairLen(Value);
	}
}

void AFPS_HUD::SetCrosshairDotSize(float Value) {
	if (MainGameCanvas) {
		MainGameCanvas->SetCrosshairDotSize(Value);
	}
}

void AFPS_HUD::SetCrosshairColor(FVector4 Color) {
	if (MainGameCanvas) {
		FLinearColor LinearColor = FLinearColor((float)Color.X / 255.0f, (float)Color.Y / 255.0f, (float)Color.Z / 255.0f);

		MainGameCanvas->SetCrosshairColor(LinearColor);
	}
}

void AFPS_HUD::SetCrosshairType(ECrossHairType CrosshairType) {
	if (MainGameCanvas) {
		MainGameCanvas->SetCrosshairType(CrosshairType);
	}
}

void AFPS_HUD::SetReloadPercentage(float Value) {
	if (MainGameCanvas) {
		MainGameCanvas->SetReloadPercentage(Value);
	}
}

void AFPS_HUD::ToggleReloadVisibility() {
	if (MainGameCanvas) {
		MainGameCanvas->ToggleReloadVisibility();
	}
}

void AFPS_HUD::ToggleHitMarker() {
	if (MainGameCanvas) {
		MainGameCanvas->ToggleHitMarker();
	}
}
