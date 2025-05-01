// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTypes/MeleeEnemy.h"

AMeleeEnemy::AMeleeEnemy() {

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	// Attach to mesh at socket
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(Weapon);

}

void AMeleeEnemy::BeginPlay(){
	Super::BeginPlay();

	// Collision for weapon should only be set when swinging
	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AMeleeEnemy::EnableHurtBoxCollision() {

	HurtBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeEnemy::DisableHurtBoxCollision() {

	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}
