// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class LEARNINGUNREALPROJ_API AMeleeEnemy : public ABasicEnemy{

	GENERATED_BODY() 

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* Weapon;

	/* Hurt Box of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HurtBox")
	UBoxComponent* HurtBox;

	bool bCanCombo = true;

	FORCEINLINE void ToggleCanCombo() { bCanCombo = !bCanCombo; }

	AMeleeEnemy();

	void BeginPlay();

	void EnableHurtBoxCollision();

	void DisableHurtBoxCollision();

protected:

	void Tick(float DeltaTime);
	
};
