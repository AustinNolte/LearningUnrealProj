#include "EnemyComponents/RangedEnemyAnimInstance.h"
#include "EnemyTypes/LongRangeEnemy.h"

void URangedEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {

	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Enemy) return;

	Speed = Enemy->GetVelocity().Size();

	bIsFalling = EnemyMovementComp->IsFalling();
	bIsJumping = Enemy->IsJumpProvidingForce();
}

void URangedEnemyAnimInstance::NativeInitializeAnimation() {

	Super::NativeInitializeAnimation();

	// cancel if no enemy owns
	if (!(TryGetPawnOwner())) return;

	Enemy = Cast<ALongRangeEnemy>(TryGetPawnOwner());

	// cancel if enemy is not set 
	if (!Enemy) return;

	EnemyMovementComp = Cast<UCharacterMovementComponent>(Enemy->GetMovementComponent());

	// cancel if EnemyMovementComp is not set
	if (!EnemyMovementComp) return;
}

void URangedEnemyAnimInstance::PlayFireMontage() {


	if (FireMontage && !Montage_IsPlaying(FireMontage)) {
		Montage_Play(FireMontage);
	}
}
