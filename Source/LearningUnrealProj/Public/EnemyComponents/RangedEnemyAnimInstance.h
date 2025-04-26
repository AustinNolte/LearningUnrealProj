// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RangedEnemyAnimInstance.generated.h"

class UAnimMontage;
class ALongRangeEnemy;
class UCharacterMovementComponent;

UCLASS()
class LEARNINGUNREALPROJ_API URangedEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/* Owner of the EnemyAnimInstance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	ALongRangeEnemy* Enemy;

	/* Owner of the EnemyAnimInstance character movement for faster referencing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	UCharacterMovementComponent* EnemyMovementComp;

	/* Shooting Gun Montage for PlayerCharacter */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire - Animation")
	UAnimMontage* FireMontage;

	/* Controls whether or not to play FireMontage*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire - Animation")
	bool bIsFiring;

	/* Controls whether or not to blend poses with shooting and left hand*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire - Animation")
	bool bUseOffHandIK = false;

	/* Socket Location FVector */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire - Animation")
	FVector IKTargetLocation;

	/* Socket Rotation FRotator */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fire - Animation")
	FRotator IKTargetRotation;

	/* Speed of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	float Speed;

	/* Controls whether or not to play falling animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bIsFalling = false;

	/* Controls whether or not to play jumping animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bIsJumping = false;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

	/* Plays firing montage if available */
	UFUNCTION(BlueprintCallable)
	void PlayFireMontage();

};
