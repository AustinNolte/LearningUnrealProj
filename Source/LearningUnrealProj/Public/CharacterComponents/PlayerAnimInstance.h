
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAnimInstance.generated.h"


class UAnimMontage;
class AFirstPersonCharacter;
class UCharacterMovementComponent; 

UCLASS()
class LEARNINGUNREALPROJ_API UPlayerAnimInstance : public UAnimInstance {

	GENERATED_BODY()
	
public:
	/* Owner of the PlayerAnimInstance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	AFirstPersonCharacter* Player; 

	/* Owner of the PlayerAnimInstance character movement for faster referencing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Animating")
	UCharacterMovementComponent* PlayerMovementComp;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bHoldingWeapon = false;

	FORCEINLINE void setbHoldingWeapon(bool Value) { bHoldingWeapon = Value; }

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

	/* Plays firing montage if available */
	UFUNCTION(BlueprintCallable)
	void PlayFireMontage();

};
