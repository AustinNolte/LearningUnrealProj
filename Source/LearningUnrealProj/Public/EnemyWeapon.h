// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponents/EnemyProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyWeapon.generated.h"


class USkeletalMeshComponent;
class UTexture2D;

UCLASS()
class LEARNINGUNREALPROJ_API AEnemyWeapon : public AActor {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AEnemyProjectile> ProjectileClass;

	// FireRate in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float FireRate;

	// bloom amount for firing a weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AlloPrivateAccess = "true"))
	float FireSpread = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	// Sets default values for this actor's properties
	AEnemyWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire(FVector3d direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FORCEINLINE class USkeletalMeshComponent* GetSkeleton() const { return SkeletalMesh; }

	FORCEINLINE float GetFireRate() const { return FireRate; }

};