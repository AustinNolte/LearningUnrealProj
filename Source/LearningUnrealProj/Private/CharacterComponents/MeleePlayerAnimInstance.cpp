#include "ThirdPersonCharacter.h"
#include "CharacterComponents/MeleePlayerAnimInstance.h"

void UMeleePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds){

	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Player) return;

	Speed = Player->GetVelocity().Size();

	bIsFalling = PlayerMovementComp->IsFalling();
	bIsJumping = Player->IsJumpProvidingForce();
}

void UMeleePlayerAnimInstance::NativeInitializeAnimation(){
	Super::NativeInitializeAnimation();

	// cancel if no player owns
	if (!(TryGetPawnOwner())) return;

	Player = Cast<AThirdPersonCharacter>(TryGetPawnOwner());

	// cancel if player is not set 
	if (!Player) return;

	PlayerMovementComp = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());

	// cancel if PlayerMovementComp is not set
	if (!PlayerMovementComp) return;
}

void UMeleePlayerAnimInstance::PlayMontage(UAnimMontage* Montage) {
	
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Montage);
	}
}

void UMeleePlayerAnimInstance::StopMontage(UAnimMontage* Montage) {
	
	Montage_Stop(0.0f, Montage);
}
