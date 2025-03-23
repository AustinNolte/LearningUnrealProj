// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"

AWeaponPickup::AWeaponPickup(){
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	
	// disabling physics for weapon so it floats
	SkeletalMesh->SetSimulatePhysics(false);

	// Set collision to overlap (instead of block)
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Only detects overlaps, no physical collision
	SkeletalMesh->SetCollisionObjectType(ECC_WorldDynamic); // Set it as a dynamic object
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore all collisions

	// making the mesh the root component
	RootComponent = SkeletalMesh;


	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpArea")); // name object
	Sphere->SetupAttachment(RootComponent); // attach to root
	Sphere->SetSphereRadius(100.0f); // set size
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // set to only check for overlap, not actually collide
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore); // ignore collision channels and masks
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // check overlap for pawns

}

void AWeaponPickup::Interact(AActor* InteractingActor) {

	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(InteractingActor);
	if (Player && WeaponClass) {
		// Spawn the actual weapon
		AWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, GetActorTransform());

		if (SpawnedWeapon) {
			// Give weapon to player
			Player->addWeapon(SpawnedWeapon);
		}

		// Destroy the pickup after use
		Destroy();
	}
}