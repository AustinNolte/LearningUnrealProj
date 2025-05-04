// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicEnemy.h"
#include "CharacterComponents/MeleePlayerAnimInstance.h"
#include "MeleeEnemy.generated.h"

class AMeleeWeapon;
class UChildActorComponent;
class UMeleePlayerAnimInstnace;

UCLASS()
class LEARNINGUNREALPROJ_API AMeleeEnemy : public ABasicEnemy{

	GENERATED_BODY() 

public:

	/* Weapon of character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowAbstract = false, AllowedClasses = "AMeleeWeapon"))
	UChildActorComponent* Weapon;

	/* Animation instance for faster referecning*/
	UMeleePlayerAnimInstance* AnimInstance;
	
protected:

	void Tick(float DeltaTime);
	
public:

	/* Returns weapon */
	UFUNCTION(BlueprintCallable)
	AMeleeWeapon* GetWeapon();

	AMeleeEnemy();

	void BeginPlay();

	/* For Light Attacks */
	UFUNCTION(BlueprintCallable)
	void LightAttack();

	/* For Heavy Attacks */
	UFUNCTION(BlueprintCallable)
	void HeavyAttack();
};
