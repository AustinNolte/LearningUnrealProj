// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" 
#include "Weapon.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "AmmoAndWeaponDisplay.generated.h"

class AWeapon;
class UTextBlock;
class UImage;

UCLASS()
class LEARNINGUNREALPROJ_API UAmmoAndWeaponDisplay : public UUserWidget{
	GENERATED_BODY()

public:

	UAmmoAndWeaponDisplay(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	/* Takes in currammo and MAX_AMMO in order to format a string to display current amount */
	void UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO);

	/* Resets Ammo to MAX_AMMO */
	void ResetAmmo(int32 MAX_AMMO);

	/* Changes weapon, this includes weapon icon and ammo count etc */
	void ChangeWeapon(AWeapon* NewWeapon);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AmmoDisplay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* WeaponImage;


};
