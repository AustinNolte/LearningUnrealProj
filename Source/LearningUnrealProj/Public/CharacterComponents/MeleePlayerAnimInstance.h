// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MeleePlayerAnimInstance.generated.h"

class AThirdPersonCharacter;
class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMontageNotifyEvent, FName, NotifyName);

UCLASS()
class LEARNINGUNREALPROJ_API UMeleePlayerAnimInstance : public UAnimInstance{

	GENERATED_BODY()
	
public:

	/* Owner of the AnimInstance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	AThirdPersonCharacter* Player;

	/* Owner of the AnimInstance's character movement for faster referencing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	UCharacterMovementComponent* PlayerMovementComp;

	/* Speed of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	float Speed;

	/* Controls whether or not to play falling animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bIsFalling = false;

	/* Controls whether or not to play jumping animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bIsJumping = false;

	// Broadcast this when a notify fires
	UPROPERTY(BlueprintAssignable, Category = "Animation Notifies")
	FMontageNotifyEvent OnNotifyBegin;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
	void PlayMontage(UAnimMontage* Montage);

	UFUNCTION(BlueprintCallable)
	void StopMontage(UAnimMontage* Montage);
};
