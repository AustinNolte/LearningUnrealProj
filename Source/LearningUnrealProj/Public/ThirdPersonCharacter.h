// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterComponents/MeleePlayerAnimInstance.h"
#include "MeleeWeapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interactable.h"
#include "ThirdPersonCharacter.generated.h"

class UMeleePlayerAnimInstance;

UCLASS()
class LEARNINGUNREALPROJ_API AThirdPersonCharacter : public ACharacter{

	GENERATED_BODY()

public:

	/* Health of Player default 500 set from MAX_HEALTH */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;

	/* Health Regen Rate: Regeneration per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float HealthRegenRate = 5;

	/* Default 500 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MAX_HEALTH = 500;

	/* Default RegenDelay of Health in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float HealthRegenDelay = 5.0f;
	
	/* Stamina of Player default 100 set from MAX_STAMINA */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Stamina;

	/* Stamina Regen Rate: Regeneration Per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float StaminaRegenRate = 5;

	/* Max Stamina Default 100 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MAX_STAMINA = 100;
	
	/* Default RegenDelay of Health in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float StaminaRegenDelay = 5.0f;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/* LightAttack InputAction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* LightAttackAction;

	/* MediumAttack InputAction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* MediumAttackAction;

	/* HeavyAttack InputAction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* HeavyAttackAction;

	/* SpecialAttack InputAction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SpecialAttackAction;


	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/* Weapon of character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowAbstract = false, AllowedClasses = "AMeleeWeapon"))
	UChildActorComponent* Weapon;

	/* Animation instance for faster referecning*/
	UMeleePlayerAnimInstance* AnimInstance;

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

	void BeginPlay();

protected:

	void Tick(float DeltaTime);

	/** ------------------------ INPUT SECTION ------------------------ **/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyControllerChanged() override;

	/** ------------------------ INPUT HANDLING SECTION ------------------------ **/

	//** Called for Movement Input */
	virtual void Move(const FInputActionValue& Value);

	//** Called for Looking Input */
	virtual void Look(const FInputActionValue& Value);

	//** Called for Interact Input */
	virtual void Interact(const FInputActionValue& Value);

	/* For Light Attacks */
	virtual void LightAttack(const FInputActionValue& Value);

	/* For Medium Attacks */
	virtual void MediumAttack(const FInputActionValue& Value);

	/* For Heavy Attacks */
	virtual void HeavyAttack(const FInputActionValue& Value);

	/* For Special Attacks */
	virtual void SpecialAttack(const FInputActionValue& Value);

public:


	bool bWantsToCombo = false;
	bool bAttacking = false;
	bool bEnemyHitDuringAttack = false;

	FORCEINLINE void EnableEnemyHitDuringAttack() { bEnemyHitDuringAttack = true; }

	int CurrentAttackIndex = 0;

	int GetCurrentAttackIndex();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void AttackCombo(FAttackData Data);
	FAttackData CurrentAttackData;

	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void DisableComboWindow();

	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void EnableComboWindow();

	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void EnableWeaponHurtBox();

	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void DisableWeaponHurtBox();
	 
	/* Handler for Anim Noitfy in blueprints*/
	UFUNCTION(BlueprintCallable)
	void ResetAttackState();
	
	/* Handler for Anim Notify in blueprints*/
	UFUNCTION(BlueprintCallable)
	void LastHit();

private:
	


	void StartStaminaRegenDelay();
	void StartHelathRegenDelay();

	bool bRegenStamina = false;
	bool bRegenHealth = false;

	FORCEINLINE void EnableStaminaRegen() { bRegenStamina = true; }
	FORCEINLINE void EnableHealthRegen()  { bRegenHealth  = true; }


	FTimerHandle HealthRegenTimer;
	FTimerHandle StaminaRegenTimer;

};
