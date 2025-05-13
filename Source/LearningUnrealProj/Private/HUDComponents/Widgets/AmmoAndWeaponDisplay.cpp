#include "HUDComponents/Widgets/AmmoAndWeaponDisplay.h"

UAmmoAndWeaponDisplay::UAmmoAndWeaponDisplay(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UAmmoAndWeaponDisplay::NativeConstruct(){
	Super::NativeConstruct();
}

void UAmmoAndWeaponDisplay::UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO){
	if (AmmoDisplay) {
		FString AmmoString = FString::Printf(TEXT("%d / %d"), CurrAmmo, MAX_AMMO);
		FText AmmoText = FText::FromString(AmmoString);
		AmmoDisplay->SetText(AmmoText);
	}
}

void UAmmoAndWeaponDisplay::ResetAmmo(int32 MAX_AMMO){
	if (AmmoDisplay) {
		FString AmmoString = FString::Printf(TEXT("%d / %d"), MAX_AMMO, MAX_AMMO);
		FText AmmoText = FText::FromString(AmmoString);
		AmmoDisplay->SetText(AmmoText);
	}
}

void UAmmoAndWeaponDisplay::ChangeWeapon(AWeapon* NewWeapon){
	if (NewWeapon) {
		UpdateAmmo(NewWeapon->CurrentAmmo, NewWeapon->MAX_AMMO);
		UTexture2D* WeaponTexture = NewWeapon->hudTexture;
		
		// check that weapontexture is set
		if (WeaponTexture && WeaponImage) {

			WeaponImage->SetBrushFromTexture(WeaponTexture);
		}
	}
}
