#include "CharacterComponents/PlayerAnimInstance.h"
#include "FirstPersonCharacter.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds){

	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Player) return; 

	Speed = Player->GetVelocity().Size();

	bIsFalling = PlayerMovementComp->IsFalling();
	bIsJumping = Player->IsJumpProvidingForce();
}

void UPlayerAnimInstance::NativeInitializeAnimation(){

	Super::NativeInitializeAnimation();

	// cancel if no player owns
	if (!(TryGetPawnOwner())) return;

	Player = Cast<AFirstPersonCharacter>(TryGetPawnOwner());
		
	// cancel if player is not set 
	if (!Player) return;

	PlayerMovementComp = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());

	// cancel if PlayerMovementComp is not set
	if (!PlayerMovementComp) return;
}

void UPlayerAnimInstance::PlayFireMontage(){


	if (FireMontage && !Montage_IsPlaying(FireMontage)){
		Montage_Play(FireMontage);
	}
}
