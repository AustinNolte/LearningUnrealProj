#include "HUDComponents/FPS_HUD.h"

AFPS_HUD::AFPS_HUD(){

}

void AFPS_HUD::DrawHUD(){
	Super::DrawHUD();
}

void AFPS_HUD::BeginPlay(){
	Super::BeginPlay();

	if (MainGameUIClass && GetWorld()) {
		
		MainGameCanvas = CreateWidget<UMainCanvas>(GetWorld(), MainGameUIClass);
		if (MainGameCanvas) {
			MainGameCanvas->AddToViewport();
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

void AFPS_HUD::ResetHealth(){

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
	MainGameCanvas->UpdateAmmo(CurrAmmo, MAX_AMMO);
}

void AFPS_HUD::ResetAmmo(int32 MAX_AMMO) {
	MainGameCanvas->ResetAmmo(MAX_AMMO);
}

void AFPS_HUD::ChangeWeapon(AWeapon* NewWeapon) {
	MainGameCanvas->ChangeWeapon(NewWeapon);
}
