// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "MeleePlayerAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class LEARNINGUNREALPROJ_API UMeleePlayerAnimInstance : public UAnimInstance{

	GENERATED_BODY()
	
public:

	/* Owner of the AnimInstance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	ACharacter* Character;

	/* Owner of the AnimInstance's character movement for faster referencing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	UCharacterMovementComponent* CharacterMovementComp;

	/* Speed of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	float Speed;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
	void PlayMontage(UAnimMontage* Montage);

	UFUNCTION(BlueprintCallable)
	void StopMontage(UAnimMontage* Montage);
};
