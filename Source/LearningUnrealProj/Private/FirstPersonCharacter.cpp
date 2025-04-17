#include "FirstPersonCharacter.h"

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
			InteractableActor->Interact(this);

		}
	}
}

void AFirstPersonCharacter::FireWeapon(const FInputActionValue& Value) {
	
	if (equippedWeapon && canFire) {
	
		FVector3d camLoc = camera->GetComponentLocation();
		FVector3d camRot = camera->GetForwardVector();
		FVector3d endPoint = camLoc + (camRot * 1000);

		FCollisionQueryParams CollisionParams;

		//DrawDebugLine(GetWorld(), camLoc, endPoint, FColor::Green, false, 1, 0, 1);

		FHitResult OutHit;
		if (GetWorld()->LineTraceSingleByChannel(OutHit, camLoc, endPoint, ECC_Pawn, CollisionParams)){
			//UE_LOG(LogTemp, Warning, TEXT("Hit at Location: %s"), *OutHit.Location.ToString());
			 
		}

		//UE_LOG(LogTemp, Warning, TEXT("Actors Current Forward Vector: %s"), *GetActorForwardVector().ToString());
		FVector3d shotDirection =  endPoint - equippedWeapon->GetSkeleton()->GetSocketLocation("ProjectileSpawn");
		shotDirection.Normalize();
		equippedWeapon->Fire(shotDirection);



		canFire = false;
		timeSinceLastFire = 0.0f;
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

//** ------------------------ INVENTORY SECTION ------------------------ **/

void AFirstPersonCharacter::addWeapon(AWeapon* weapon) {
	
	Inventory->addWeapon(weapon);

	OnWeaponAdded.Broadcast(weapon);

	equipWeapon(weapon);
}

void AFirstPersonCharacter::equipWeapon(AWeapon* weapon) {
	
	if (equippedWeapon != nullptr) {
		equippedWeapon->GetSkeleton()->SetVisibility(false);
		equippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
	equippedWeapon = weapon;
	(equippedWeapon->GetSkeleton())->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
	equippedWeapon->GetSkeleton()->SetVisibility(true);

	HasWeapon = true;
	OnWeaponChanged.Broadcast(equippedWeapon);
}

void AFirstPersonCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (equippedWeapon) {
		
		timeSinceLastFire += DeltaTime;

		if (timeSinceLastFire >= equippedWeapon->GetFireRate() && !canFire) {

			canFire = true;
		}
	}
}