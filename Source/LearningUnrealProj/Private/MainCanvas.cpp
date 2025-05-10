#include "MainCanvas.h"

UMainCanvas::UMainCanvas(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UMainCanvas::NativeConstruct(){
	Super::NativeConstruct();
}

/*------------- Health Bar Section ---------------- */

void UMainCanvas::UpdateHealth(float Value){
	if (HealthBarWidget) {
		HealthBarWidget->UpdateHealth(Value);	
	}
}

void UMainCanvas::ResetHealth(){
	if (HealthBarWidget) {
		HealthBarWidget->ResetHealth();
	}
}

/*------------- Stamina Bar Section ---------------- */

void UMainCanvas::UpdateStamina(float Value){
	if (StaminaBarWidget) {
		StaminaBarWidget->UpdateStamina(Value);
	}
}

void UMainCanvas::ResetStamina(){
	if (StaminaBarWidget) {
		StaminaBarWidget->ResetStamina();
	}
}

/*------------- Ammo and Weapon Section ---------------- */

void UMainCanvas::UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO){
	if (AmmoAndWeaponDisplay) {
		AmmoAndWeaponDisplay->UpdateAmmo(CurrAmmo, MAX_AMMO);
	}
}

void UMainCanvas::ResetAmmo(int32 MAX_AMMO){
	if (AmmoAndWeaponDisplay) {
		AmmoAndWeaponDisplay->ResetAmmo(MAX_AMMO);
	}
}

void UMainCanvas::ChangeWeapon(AWeapon* NewWeapon){
	if (AmmoAndWeaponDisplay) {
		AmmoAndWeaponDisplay->ChangeWeapon(NewWeapon);
	}
}

void UMainCanvas::ToggleAmmoAndWeaponDisplay(){
	if (AmmoAndWeaponDisplay) {
		if (AmmoAndWeaponDisplay->GetVisibility() == ESlateVisibility::Hidden) {
			AmmoAndWeaponDisplay->SetVisibility(ESlateVisibility::Visible);
			if (AmmoAndWeaponDisplayBackground) {
				AmmoAndWeaponDisplayBackground->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else if (AmmoAndWeaponDisplay->GetVisibility() == ESlateVisibility::Visible) {
			AmmoAndWeaponDisplay->SetVisibility(ESlateVisibility::Hidden);
			if (AmmoAndWeaponDisplayBackground) {
				AmmoAndWeaponDisplayBackground->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

/*------------ Crosshair Section -------------------------*/

void UMainCanvas::SetCrosshairThickness(float Value){
	if (CrosshairComponent) {
		CrosshairComponent->SetCrosshairThickness(Value);
	}
}

void UMainCanvas::SetCrosshairGap(float Value){
	if (CrosshairComponent) {
		CrosshairComponent->SetCrosshairGap(Value);
	}
}

void UMainCanvas::SetCrosshairLen(float Value){
	if (CrosshairComponent) {
		CrosshairComponent->SetCrosshairLen(Value);
	}
}

void UMainCanvas::SetCrosshairDotSize(float Value){
	if (CrosshairComponent) {
		CrosshairComponent->SetCrosshairDotSize(Value);
	}
}

void UMainCanvas::SetCrosshairColor(FLinearColor Color){
	if (CrosshairComponent) {
		CrosshairComponent->SetCrosshairColor(Color);
	}
}

void UMainCanvas::SetCrosshairType(ECrossHairType CrosshairType){
	if (CrosshairComponent) {
		CrosshairComponent->SetCrosshairType(CrosshairType);
	}
}

void UMainCanvas::SetReloadPercentage(float Value){
	if (CrosshairComponent) {
		CrosshairComponent->SetReloadPercentage(Value);
	}
}

void UMainCanvas::ToggleReloadVisibility() {
	if (CrosshairComponent) {
		CrosshairComponent->ToggleReloadVisibility();
	}
}

void UMainCanvas::ToggleHitMarker(){
	if (CrosshairComponent) {
		CrosshairComponent->ToggleHitMarker();
	}
}
