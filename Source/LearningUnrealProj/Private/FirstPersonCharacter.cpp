#include "FirstPersonCharacter.h"
#include <WeaponPickup.h>

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Adjusting Size of Physics Component
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(GetCapsuleComponent());
	camera->bUsePawnControlRotation = true;

	Inventory = CreateDefaultSubobject<UInventoryManager>(TEXT("InventoryManager"));

}

void AFirstPersonCharacter::BeginPlay(){
	Super::BeginPlay();

	UPlayerAnimInstance* AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
	if (AnimInstance) {
		AnimationInstance = AnimInstance;
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	
	// wanting fast arcade style movement
	
	GetCharacterMovement()->MaxAcceleration = 999999; 
	GetCharacterMovement()->BrakingFrictionFactor = 100.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 10000.0f;
	GetCharacterMovement()->AirControl = 1.0f;

	// toggle hud to fps mode 
	AFPS_HUD* HUD = GetHud();

	if (HUD) {
		HUD->ToggleFPSMode();
	}


}

void AFirstPersonCharacter::NotifyControllerChanged() {

	Super::NotifyControllerChanged();

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}



// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	// Setup action bindings
	if (UEnhancedInputComponent* EnhancedIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jump input
		EnhancedIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::Jump);
		EnhancedIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::StopJumping);

		// Move Input
		EnhancedIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Move);

		// Look Input
		EnhancedIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Look);

		// Interact Input
		EnhancedIC->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Interact);

		// Fire Input
		EnhancedIC->BindAction(FireAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::FireWeapon); 
		 
		// Change Weapon Input
		EnhancedIC->BindAction(ChangeWeaponAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::ChangeWeapon);

		// Hold to Sprint
		EnhancedIC->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::StartSprint);
		EnhancedIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::StopSprint);

		// Reload Input
		EnhancedIC->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::ReloadWeapon);

	}
}

/** ------------------------ INPUT HANDLING SECTION ------------------------ **/
void AFirstPersonCharacter::Move(const FInputActionValue& Value) {

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr){

		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFirstPersonCharacter::Look(const FInputActionValue& Value) {

	// input is a Vector2D
	FVector2D LookVector = Value.Get<FVector2D>();

	// dividing by 4 as the default is too fast to really get a good control on the lower end for a custom sens
	LookVector /= 4;

	LookVector *= Sensitivity;

	if (Controller != nullptr) {

		// add look input
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);

	}
}


void AFirstPersonCharacter::Interact(const FInputActionValue& Value) {


	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors) {

		AInteractable* InteractableActor = Cast<AInteractable>(Actor);
		if (InteractableActor) {
			if (AWeaponPickup* WeaponPickup = Cast <AWeaponPickup> (InteractableActor)) {
				// don't want to interact with weapon pickup if realoding weapon
				if (bReloading) {
					return;
				}
			}
			InteractableActor->Interact(this);

		}
	}
}

void AFirstPersonCharacter::FireWeapon(const FInputActionValue& Value) {
	
	if (equippedWeapon && canFire && (!(equippedWeapon->bIsReloading)) && (equippedWeapon->CurrentAmmo >= 1)) {
	
		FVector3d camLoc = camera->GetComponentLocation();
		FVector3d camRot = camera->GetForwardVector();
		FVector3d endPoint = camLoc + (camRot * 1000);

		FCollisionQueryParams CollisionParams;

		FHitResult OutHit;
		if (GetWorld()->LineTraceSingleByChannel(OutHit, camLoc, endPoint, ECC_Pawn, CollisionParams)){
			//UE_LOG(LogTemp, Warning, TEXT("Hit at Location: %s"), *OutHit.Location.ToString());
			 
		}

		FVector3d shotDirection =  endPoint - equippedWeapon->GetSkeleton()->GetSocketLocation("ProjectileSpawn");
		shotDirection.Normalize();
		if(equippedWeapon->Fire(shotDirection)){
		
			AFPS_HUD* HUD = GetHud();
			if (HUD) {
				HUD->UpdateAmmo(equippedWeapon->CurrentAmmo, equippedWeapon->MAX_AMMO);
			}
		}

		if (AnimationInstance){
			AnimationInstance->PlayFireMontage();
		}

		canFire = false;
		timeSinceLastFire = 0.0f;
	}
	if (equippedWeapon && equippedWeapon->CurrentAmmo == 0) {
		if ((!bReloading)) {
			equippedWeapon->Reload();
			timeSinceStartReload = 0;
			bReloading = true;
			AFPS_HUD* HUD = GetHud();
			if (HUD) {
				HUD->ToggleReloadVisibility();
			}
		}
	}
}

void AFirstPersonCharacter::ChangeWeapon(const FInputActionValue& Value) {
	
	// quick return for if there is nothing in inventory, no need to traverse the rest of the code
	if (Inventory->getWeaponInventoryLen() == 0) {
		return;
	}
	// -1 to make the calls easier for array indexing
	int index = (int)Value.Get<float>() - 1;

	AWeapon* newWeapon = Inventory->getWeaponAtIndex(index);

	if (newWeapon == nullptr) {
		return;
	} else {
		equipWeapon(newWeapon);
	}
}

void AFirstPersonCharacter::ReloadWeapon(const FInputActionValue& Value){
	if (equippedWeapon && (!bReloading)) {
		equippedWeapon->Reload();
		timeSinceStartReload = 0;
		bReloading = true;
		AFPS_HUD* HUD = GetHud();
		if (HUD) {
			HUD->ToggleReloadVisibility();
		}
	}
}

void AFirstPersonCharacter::StartSprint(const FInputActionValue& Value){
	if (Stamina > 0) {
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; 
		StartStaminaRegenDelay();
	}

}

void AFirstPersonCharacter::StopSprint(const FInputActionValue& Value) {
	if (bIsSprinting) {
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
}

void AFirstPersonCharacter::StartStaminaRegenDelay() {
	GetWorld()->GetTimerManager().SetTimer(
		StaminaRegenTimer,
		this,
		&AFirstPersonCharacter::EnableStaminaRegen,
		StaminaRegenDelay,   // Delay in seconds
		false   // Don't loop
	);
	UE_LOG(LogTemp, Warning, TEXT("Stamina Regen Set: %f"), Stamina);
}

void AFirstPersonCharacter::StartHelathRegenDelay() {
	GetWorld()->GetTimerManager().SetTimer(
		HealthRegenTimer,
		this,
		&AFirstPersonCharacter::EnableHealthRegen,
		HealthRegenDelay,   // Delay in seconds
		false   // Don't loop
	);
}

//** ------------------------ INVENTORY SECTION ------------------------ **/

void AFirstPersonCharacter::addWeapon(AWeapon* weapon) {
	
	Inventory->addWeapon(weapon);
	UE_LOG(LogTemp, Warning, TEXT("InventoryLen: %d"), Inventory->getWeaponInventoryLen());
	// turn on at the first weapon added
	if (Inventory->getWeaponInventoryLen() == 1) {
		
		AFPS_HUD* HUD = GetHud(); 
		if (HUD) {
			HUD->ToggleAmmoAndWeaponDisplay();
		}
	}

	OnWeaponAdded.Broadcast(weapon);
	equipWeapon(weapon);

	// add weapon reloading event/delegate
	weapon->OnReloadDone.AddDynamic(this, &AFirstPersonCharacter::ReloadHepler);

}

void AFirstPersonCharacter::equipWeapon(AWeapon* weapon) {
	if (!bReloading) {
		if (equippedWeapon != nullptr) {
			equippedWeapon->GetSkeleton()->SetVisibility(false);
			equippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
		equippedWeapon = weapon;
		(equippedWeapon->GetSkeleton())->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
		equippedWeapon->GetSkeleton()->SetVisibility(true);

		HasWeapon = true;
		if (AnimationInstance) {
			AnimationInstance->setbHoldingWeapon(HasWeapon);
		}
		OnWeaponChanged.Broadcast(equippedWeapon);
		AFPS_HUD* HUD = GetHud();
		if (HUD) {
			HUD->ChangeWeapon(equippedWeapon);
		}
	}
}

void AFirstPersonCharacter::ReloadHepler(int32 AmmoCount){
	
	bReloading = false;

	AFPS_HUD* HUD = GetHud();
	if (HUD) {
		HUD->ResetAmmo(AmmoCount);
		HUD->ToggleReloadVisibility();
	}
}

void AFirstPersonCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (equippedWeapon && !canFire) {
		
		timeSinceLastFire += DeltaTime;

		if (timeSinceLastFire >= equippedWeapon->GetFireRate() && !canFire) {

			canFire = true;
		}
	}

	// will lose stamina 1.5x faster than regenerated 
	if (bIsSprinting) {
		Stamina -= (StaminaRegenRate * 1.5f) * DeltaTime;
		AFPS_HUD* HUD = GetHud();
		if (HUD) {
			HUD->UpdateStamina(Stamina / MAX_STAMINA);
		}
	}

	if (bRegenHealth) {
		Health = Health + (HealthRegenRate * DeltaTime);

		AFPS_HUD* HUD = GetHud();

		if (HUD) {
			HUD->UpdateHealth(Health / MAX_HEALTH);
		}

		if (Health > MAX_HEALTH) {
			Health = MAX_HEALTH;
			bRegenHealth = false;

			HUD->UpdateHealth(Health / MAX_HEALTH);

		}
	}
	if (bRegenStamina) {
		Stamina = Stamina + (StaminaRegenRate * DeltaTime);
		AFPS_HUD* HUD = GetHud();
		
		if (HUD) {
			HUD->UpdateStamina(Stamina / MAX_STAMINA);
		}

		if (Stamina > MAX_STAMINA) {
			Stamina = MAX_STAMINA;
			bRegenStamina = false;

			HUD->UpdateStamina(Stamina / MAX_STAMINA);

		}
	}

	if (bReloading) {
		timeSinceStartReload += DeltaTime;
		AFPS_HUD* HUD = GetHud();
		if (HUD) {
			HUD->SetReloadPercentage(timeSinceStartReload / equippedWeapon->ReloadTime);
		}
	}
} 


/* Helper Functions */

/* Returns HUD already casted to correct type */
AFPS_HUD* AFirstPersonCharacter::GetHud(){

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC && PC->GetHUD()) {
		AFPS_HUD* HUD = Cast<AFPS_HUD>(PC->GetHUD());
		if (HUD){
			return HUD;
		}
	}
	return nullptr;
}

// Using Kismet GameplayStatistics functions for damage
float AFirstPersonCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {

	Health -= DamageAmount;

	if (bRegenHealth) {
		bRegenHealth = false;
	}

	AFPS_HUD* HUD = GetHud();
	if (HUD) {
		HUD->UpdateHealth(Health / MAX_HEALTH);
	}

	StartHelathRegenDelay();

	if (Health <= 0) {
		Die();
	}

	return DamageAmount;
}
