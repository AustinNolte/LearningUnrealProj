// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class USkeletalMeshComponent;
class UTexture2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReloadDone, int32, AmmoCount);

UCLASS()
class LEARNINGUNREALPROJ_API AWeapon : public AActor {

	GENERATED_BODY()

public:

	/* Projectile for Current Weapon to shoot */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	/* FireRate in seconds, higher is slower */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float FireRate;

	/* bloom amount for firing a weapon, higher is more spread */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AlloPrivateAccess = "true"))
	float FireSpread = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;
	
	/* Texture for Hotbar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Image", meta = (AllowPrivateAccess = "true"))
	UTexture2D* hudTexture;
	
	/* Weapon Name for Hud */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Attributes", meta = (AllowPrivateAccess = "true"))
	FString WeaponName;

	UPROPERTY(BlueprintAssignable, Category = "ReloadTiming")
	FOnReloadDone OnReloadDone;

	/* Max Ammo of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 MAX_AMMO = 30;

	/* Current Ammo in the clip */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 CurrentAmmo = 30;
 
	/* Determines if the weapon is reloading*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	bool bIsReloading = false;

	/* Controls how fast the reload is, lower is faster */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float ReloadTime; 

	/* Timer for Reloading Weapon */
	FTimerHandle ReloadTimerHandle;

	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Fire(FVector3d direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// helper function to perform the reload 
	void ReloadHelper();

public:

	FORCEINLINE class USkeletalMeshComponent* GetSkeleton() const { return SkeletalMesh; }

	FORCEINLINE float GetFireRate() const { return FireRate; }	

	UFUNCTION(BlueprintCallable, Category = "Hud Manipulation")
	FORCEINLINE class UTexture2D* GetWeaponTexture() const { return hudTexture; }

	FORCEINLINE class FString GetWeaponName() const { return WeaponName; }

	FORCEINLINE int8 GetCurrentAmmo() { return CurrentAmmo; }

	FORCEINLINE bool GetIsRelolading() { return bIsReloading;  }

	void Reload();
	
};