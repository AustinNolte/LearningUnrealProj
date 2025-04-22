#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponents/Projectile.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AWeapon::AWeapon(){

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	// diable physics
	SkeletalMesh->SetSimulatePhysics(false);

	// Set collision to overlap (instead of block)
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Only detects overlaps, no physical collision
	SkeletalMesh->SetCollisionObjectType(ECC_WorldDynamic); // Set it as a dynamic object
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore all collisions

	// making the mesh the root component
	RootComponent = SkeletalMesh;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay(){
	
	Super::BeginPlay();
	
}
// Shoots towards Direction with a given bloom associated with the current weapon being used held in FireSpread
void AWeapon::Fire(FVector3d direction) {

	UWorld* const World = GetWorld();

	if (World != nullptr && (CurrentAmmo > 0)) {

		FVector3d spawnLocation = SkeletalMesh->GetSocketLocation("ProjectileSpawn");
		//UE_LOG(LogTemp, Warning, TEXT("Direction of shot: %s"), *direction.ToString());

		FRotator spawnRotation = direction.Rotation();

		spawnRotation.Yaw += FMath::FRandRange(-FireSpread, FireSpread);
		spawnRotation.Pitch += FMath::FRandRange(-FireSpread, FireSpread);


		//Set Spawn Collision Handling Override
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<AProjectile>(ProjectileClass, spawnLocation, spawnRotation, actorSpawnParams);

		--CurrentAmmo;
		UE_LOG(LogTemp, Warning, TEXT("Here in Weapon, Current AMMO: %d"), CurrentAmmo);
		if (CurrentAmmo <= 0) {
			Reload();
		}
	}
}

void AWeapon::Reload(){
	bIsReloading = true;
	UE_LOG(LogTemp, Warning, TEXT("Here in Weapon Reload"));
	GetWorldTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&AWeapon::ReloadHelper,
		ReloadTime,
		false
	);
}

void AWeapon::ReloadHelper() {

	UE_LOG(LogTemp, Warning, TEXT("Here in Weapon ReloadHelper"));

	CurrentAmmo = MaxAmmo;
	bIsReloading = false;
}


void AWeapon::Tick(float DeltaTime) {}