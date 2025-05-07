#include "MainCanvas.h"

UMainCanvas::UMainCanvas(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UMainCanvas::NativeConstruct(){
	Super::NativeConstruct();
}

/*------------- Health Bar Section ---------------- */

void UMainCanvas::UpdateHealth(float Value){
	HealthBarWidget->UpdateHealth(Value);
}

void UMainCanvas::ResetHealth(){
	HealthBarWidget->ResetHealth();
}

/*------------- Stamina Bar Section ---------------- */

void UMainCanvas::UpdateStamina(float Value){
	StaminaBarWidget->UpdateStamina(Value);
}

void UMainCanvas::ResetStamina(){
	StaminaBarWidget->ResetStamina();
}

/*------------- Ammo and Weapon Section ---------------- */

void UMainCanvas::UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO){
	AmmoAndWeaponDisplay->UpdateAmmo(CurrAmmo, MAX_AMMO);
}

void UMainCanvas::ResetAmmo(int32 MAX_AMMO){
	AmmoAndWeaponDisplay->ResetAmmo(MAX_AMMO);
}

void UMainCanvas::ChangeWeapon(AWeapon* NewWeapon){
	AmmoAndWeaponDisplay->ChangeWeapon(NewWeapon);
}

/*------------ Crosshair Section -------------------------*/

void UMainCanvas::SetCrosshairThickness(float Value){
	CrosshairComponent->SetCrosshairThickness(Value);
}

void UMainCanvas::SetCrosshairGap(float Value){
	CrosshairComponent->SetCrosshairGap(Value);
}

void UMainCanvas::SetCrosshairLen(float Value){
	CrosshairComponent->SetCrosshairLen(Value);
}

void UMainCanvas::SetCrosshairColor(FLinearColor Color){
	CrosshairComponent->SetCrosshairColor(Color);
}

void UMainCanvas::SetCrosshairType(ECrossHairType CrosshairType){
	CrosshairComponent->SetCrosshairType(CrosshairType);
}


