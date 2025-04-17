// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTypes/LongRangeEnemy.h"

ALongRangeEnemy::ALongRangeEnemy() {
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponComponent"));

	// Attach to mesh at socket
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

}

void ALongRangeEnemy::BeginPlay() {
	if (WeaponClass){
		Weapon->SetChildActorClass(WeaponClass);
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Target = Cast<AFirstPersonCharacter>(PlayerCharacter);
}


void ALongRangeEnemy::FireWeapon(){

	if (Weapon && canFire) {

		
		FVector3d endPoint = Target->GetActorLocation();
		FVector3d Direction = endPoint - Cast<AWeapon>(Weapon->GetChildActor())->GetSkeleton()->GetSocketLocation("ProjectileSpawn");

		Direction.Normalize();
		Cast<AWeapon>(Weapon->GetChildActor())->Fire(Direction);
	}
}

void ALongRangeEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (Weapon) {
		
		timeSinceLastFire += DeltaTime;

		if (timeSinceLastFire >= Cast<AWeapon>(Weapon->GetChildActor())->GetFireRate() && !canFire) {
			canFire = true;
		}
	}
}

