#include "CharacterComponents/MeleePlayerAnimInstance.h"
#include "ThirdPersonCharacter.h"

void UMeleePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds){

	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character) return;

	Speed = Character->GetVelocity().Size();
}

void UMeleePlayerAnimInstance::NativeInitializeAnimation(){
	Super::NativeInitializeAnimation();

	// cancel if no player owns
	if (!(TryGetPawnOwner())) return;

	Character = Cast<ACharacter>(TryGetPawnOwner());

	// cancel if owner is not set 
	if (!Character) return;

	CharacterMovementComp = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());

	// cancel if PlayerMovementComp is not set
	if (!CharacterMovementComp) return;
}

void UMeleePlayerAnimInstance::PlayMontage(UAnimMontage* Montage) {
	
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Montage);
	}
}

void UMeleePlayerAnimInstance::StopMontage(UAnimMontage* Montage) {
	
	Montage_Stop(0.0f, Montage);
}
