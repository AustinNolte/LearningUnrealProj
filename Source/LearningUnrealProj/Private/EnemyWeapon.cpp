#include "EnemyWeapon.h"

// Sets default values
AEnemyWeapon::AEnemyWeapon() {

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	// diable physics
	SkeletalMesh->SetSimulatePhysics(false);

	// Set collision to overlap (instead of block)
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Only detects overlaps, no physical collision
	SkeletalMesh->SetCollisionObjectType(ECC_WorldDynamic); // Set it as a dynamic object
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore all collisions

	// making the mesh the root component
	RootComponent = SkeletalMesh;

}

// Called when the game starts or when spawned
void AEnemyWeapon::BeginPlay() {

	Super::BeginPlay();

}
// Shoots towards Direction with a given bloom associated with the current weapon being used held in FireSpread
void AEnemyWeapon::Fire(FVector3d direction) {

	UWorld* const World = GetWorld();

	if (World != nullptr) {

		FVector3d spawnLocation = SkeletalMesh->GetSocketLocation("ProjectileSpawn");
		//UE_LOG(LogTemp, Warning, TEXT("Direction of shot: %s"), *direction.ToString());

		FRotator spawnRotation = direction.Rotation();

		spawnRotation.Yaw += FMath::FRandRange(-FireSpread, FireSpread);
		spawnRotation.Pitch += FMath::FRandRange(-FireSpread, FireSpread);


		//Set Spawn Collision Handling Override
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<AEnemyProjectile>(ProjectileClass, spawnLocation, spawnRotation, actorSpawnParams);
	}
}

void AEnemyWeapon::Tick(float DeltaTime) {}