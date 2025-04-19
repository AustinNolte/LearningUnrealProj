#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h" // for testing line traces
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "CharacterComponents/InventoryManager.h"
#include "GameFramework/PlayerState.h"
#include "Weapon.h"
#include "Interactable.h"
#include "CharacterComponents/PlayerAnimInstance.h"
#include "FirstPersonCharacter.generated.h"

class UInputComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USkeletalMeshComponent;
class UCameraComponent;
class UInventoryManager; 
class UPlayerAnimInstance;
class AWeapon;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAdded, AWeapon*, Weapon);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, AWeapon*, Weapon);

UCLASS(config = Game)
class LEARNINGUNREALPROJ_API AFirstPersonCharacter : public ACharacter{
	
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

	/* Animation Asset for quick referencing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UPlayerAnimInstance* AnimationInstance; 

	/** Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* camera;

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

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** ChangeWeapon Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeWeaponAction;

	/* Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SprintAction; 


	/* Max Sprint Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	float MaxSprintSpeed = 900.0f;

	/* Max acceleration when sprinting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	float MaxAccelerationSpeed = 3072.0f;

	/* Default Sprint Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	float DefaultSprintSpeed = 600.0f; 

	/* Default acceleration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	float DefaultAccelerationSpeed = 2048.0f;
	
protected:

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

	//** Called for Fire Input */
	virtual void FireWeapon(const FInputActionValue& Value);

	//** Called for change weapon */
	virtual void ChangeWeapon(const FInputActionValue& Value);

	virtual void StartSprint(const FInputActionValue& Value);

	virtual void StopSprint(const FInputActionValue& Value);

	bool bIsSprinting = false;

	/** ------------------------ INVENTORY SECTION ------------------------ **/
	
	// Inventory Manager 
	UInventoryManager* Inventory;

public: 
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return camera; }

	/** Returns Inventory Manager subobject**/
	FORCEINLINE class UInventoryManager* GetInventoryManager() const { return Inventory; }

	/** add weapon to invenotry */
	virtual void addWeapon(AWeapon* weapon);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnWeaponAdded OnWeaponAdded; // Event for HotBar

	/** equip weapon from inventory */
	virtual void equipWeapon(AWeapon* weapon);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnWeaponChanged OnWeaponChanged; // Event for HotBar

	// currently equipped weapon starts out as null as there is no weapon to be equipped
	AWeapon* equippedWeapon = nullptr;

	// boolean to see if the person has a weapon or not
	bool HasWeapon = false;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE bool GetHasWeapon() const { return HasWeapon; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	/** ------------------------ WEAPON FIRERATE HANDLING ------------------------ **/
	bool canFire = true;

	float timeSinceLastFire = 0.0f;
};