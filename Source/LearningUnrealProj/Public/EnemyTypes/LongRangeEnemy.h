// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicEnemy.h"
#include "EnemyWeapon.h"
#include "FirstPersonCharacter.h"
#include "LongRangeEnemy.generated.h"

class UChildActorComponent;
class AFirstPersonCharacter;

UCLASS()
class LEARNINGUNREALPROJ_API ALongRangeEnemy : public ABasicEnemy
{
	GENERATED_BODY()

public:

	// constructor
	ALongRangeEnemy();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UChildActorComponent* Weapon;

	// target to shoot at
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AFirstPersonCharacter> Target;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AEnemyWeapon> WeaponClass;

	// Called every frame
	virtual void Tick(float DeltaTime) override;



	/** ------------------------ WEAPON FIRERATE HANDLING ------------------------ **/
	bool canFire = true;

	float timeSinceLastFire = 0.0f;

protected:

	UFUNCTION(BlueprintCallable)
	void FireWeapon();
	
};
