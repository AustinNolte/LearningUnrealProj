// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class USkeletalMeshComponent;
class UTexture2D;

UCLASS()
class LEARNINGUNREALPROJ_API AWeapon : public AActor {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	// FireRate in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Image", meta = (AllowPrivateAccess = "true"))
	UTexture2D* hudTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Attributes", meta = (AllowPrivateAccess = "true"))
	FString WeaponName;

	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire(FVector3d direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FORCEINLINE class USkeletalMeshComponent* GetSkeleton() const { return SkeletalMesh; }

	FORCEINLINE float GetFireRate() const { return FireRate; }	

	UFUNCTION(BlueprintCallable, Category = "Hud Manipulation")
	FORCEINLINE class UTexture2D* GetWeaponTexture() const { return hudTexture; }

	FORCEINLINE class FString GetWeaponName() const { return WeaponName; }
};