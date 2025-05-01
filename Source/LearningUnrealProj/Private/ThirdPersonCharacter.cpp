#include "ThirdPersonCharacter.h"

// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
	// Tick is not needed every frame, turning it off for performence boost
	PrimaryActorTick.bCanEverTick = true;

	// Adjusting Size of Physics Component
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponComponent"));

	// Attach to mesh at socket
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay(){
	Super::BeginPlay();

	AnimInstance = Cast<UMeleePlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (!AnimInstance) return;

	Stamina = MAX_STAMINA;

	Health = MAX_HEALTH;

	AMeleeWeapon* CurrWeapon = Cast<AMeleeWeapon>(Weapon->GetChildActor());
	if (CurrWeapon) {
		CurrWeapon->SetPlayerOwner(this);
	}
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (bRegenHealth) {
		Health = Health + (HealthRegenRate * DeltaTime);
		if (Health > MAX_HEALTH) {
			Health = MAX_HEALTH;
			bRegenHealth = false;
		}
	}
	if (bRegenStamina) {
		Stamina = Stamina + (StaminaRegenRate * DeltaTime);
		if (Stamina > MAX_STAMINA) {
			Stamina = MAX_STAMINA;
			bRegenStamina = false;
		}
	}
}

/** ------------------------ INPUT SECTION ------------------------ **/

void AThirdPersonCharacter::NotifyControllerChanged() {

	Super::NotifyControllerChanged();

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	// Setup action bindings
	if (UEnhancedInputComponent* EnhancedIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jump input
		EnhancedIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AThirdPersonCharacter::Jump);
		EnhancedIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AThirdPersonCharacter::StopJumping);

		// Move Input
		EnhancedIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Move);

		// Look Input
		EnhancedIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Look);

		// Interact Input
		EnhancedIC->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Interact);
		
		// LightAttackAction Input
		EnhancedIC->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::LightAttack);

		// MediumAttackAction Input
		EnhancedIC->BindAction(MediumAttackAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::MediumAttack);

		// HeavyAttackAction Input
		EnhancedIC->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::HeavyAttack);

		// SpecialAttackAction Input
		EnhancedIC->BindAction(SpecialAttackAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::SpecialAttack);
	}
}

/** ------------------------ INPUT HANDLING SECTION ------------------------ **/
void AThirdPersonCharacter::Move(const FInputActionValue& Value) {

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AThirdPersonCharacter::Look(const FInputActionValue& Value) {

	// input is a Vector2D
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {

		// add look input
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);

	}
}

void AThirdPersonCharacter::Interact(const FInputActionValue& Value) {

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors) {

		AInteractable* InteractableActor = Cast<AInteractable>(Actor);
		if (InteractableActor) {
			InteractableActor->Interact(this);
		}
	}
}

/* 
*
* Stamina Can be negative, this is to allow for a punishment of using too much as it will take longer to get to a positive number again
* 
*/

void AThirdPersonCharacter::LightAttack(const FInputActionValue& Value){
	FAttackData AttackData = Cast<AMeleeWeapon>(Weapon->GetChildActor())->GetLightAttackData();
	AttackCombo(AttackData);
}

void AThirdPersonCharacter::MediumAttack(const FInputActionValue& Value) {
	FAttackData AttackData = Cast<AMeleeWeapon>(Weapon->GetChildActor())->GetMediumAttackData();
	AttackCombo(AttackData);
}

void AThirdPersonCharacter::HeavyAttack(const FInputActionValue& Value) {
	FAttackData AttackData = Cast<AMeleeWeapon>(Weapon->GetChildActor())->GetHeavyAttackData();
	AttackCombo(AttackData);
}

void AThirdPersonCharacter::SpecialAttack(const FInputActionValue& Value) {
	FAttackData AttackData = Cast<AMeleeWeapon>(Weapon->GetChildActor())->GetSpecialAttackData();
	AttackCombo(AttackData);
}

int AThirdPersonCharacter::GetCurrentAttackIndex(){
	if (bWantsToCombo) {
		return CurrentAttackIndex - 1;
	}else
		return CurrentAttackIndex;
}

void AThirdPersonCharacter::AttackCombo(FAttackData Data){
	if (bAttacking && !bWantsToCombo) {
		bWantsToCombo = true;
		CurrentAttackIndex++;
	}
	if (Stamina > 0 && CurrentAttackIndex < Data.StaminaPerAttack.Num()) {
		Stamina -= Data.StaminaPerAttack[CurrentAttackIndex];
		StartStaminaRegenDelay();
	}
	else {
		bAttacking = false;
		return;
	}
	if (!bAttacking) {
		CurrentAttackData = Data;
		AnimInstance->PlayMontage(Data.AttackMontages);
		bAttacking = true;
	}
}

void AThirdPersonCharacter::EnableComboWindow() {
	bEnemyHitDuringAttack = false;
	bWantsToCombo = false;
}

void AThirdPersonCharacter::DisableComboWindow(){
	if (!bWantsToCombo) {
		AnimInstance->StopMontage(CurrentAttackData.AttackMontages);
		ResetAttackState();
	}
}

void AThirdPersonCharacter::EnableWeaponHurtBox() {
	AMeleeWeapon* CurrWeapon = Cast<AMeleeWeapon>(Weapon->GetChildActor());
	if (CurrWeapon) {
		CurrWeapon->EnableHurtBox();
	}
}

void AThirdPersonCharacter::DisableWeaponHurtBox() {
	AMeleeWeapon* CurrWeapon = Cast<AMeleeWeapon>(Weapon->GetChildActor());
	if (CurrWeapon) {
		CurrWeapon->DisableHurtBox();
	}
}

void AThirdPersonCharacter::ResetAttackState(){
	//UE_LOG(LogTemp, Warning, TEXT("In ResetAttackState"));
	bWantsToCombo = false;
	bAttacking = false;
	bEnemyHitDuringAttack = false;
	CurrentAttackIndex = 0;
	CurrentAttackData = FAttackData();
}

// needed for last hit to ensure it hits and does correct amount of damage.
void AThirdPersonCharacter::LastHit() {
	bEnemyHitDuringAttack = false;
	bWantsToCombo = false;
}

void AThirdPersonCharacter::StartStaminaRegenDelay(){
	GetWorld()->GetTimerManager().SetTimer(
		StaminaRegenTimer,
		this,
		&AThirdPersonCharacter::EnableStaminaRegen,
		StaminaRegenDelay,   // Delay in seconds
		false   // Don't loop
	);
	UE_LOG(LogTemp, Warning, TEXT("Stamina Regen Set: %f"), Stamina);
}

void AThirdPersonCharacter::StartHelathRegenDelay(){
	GetWorld()->GetTimerManager().SetTimer(
		HealthRegenTimer,
		this,
		&AThirdPersonCharacter::EnableHealthRegen,
		HealthRegenDelay,   // Delay in seconds
		false   // Don't loop
	);
}
