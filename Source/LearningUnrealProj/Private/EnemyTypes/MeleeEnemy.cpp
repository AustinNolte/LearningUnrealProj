#include "MeleeWeapon.h"
#include "EnemyTypes/MeleeEnemy.h"


AMeleeEnemy::AMeleeEnemy() {

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponComponent"));

	// Attach to mesh at socket
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

}

void AMeleeEnemy::BeginPlay(){
	Super::BeginPlay();

	AnimInstance = Cast<UMeleePlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (!AnimInstance) return;

	AMeleeWeapon* CurrWeapon = Cast<AMeleeWeapon>(Weapon->GetChildActor());
	if (CurrWeapon) {
		CurrWeapon->SetEnemyOwner(this, AnimInstance);
	}

}

AMeleeWeapon* AMeleeEnemy::GetWeapon(){
	AMeleeWeapon* CurrWeapon = Cast<AMeleeWeapon>(Weapon->GetChildActor());
	if (CurrWeapon) {
		return CurrWeapon;
	}
	else {
		return nullptr;
	}
}

void AMeleeEnemy::LightAttack(){
	AMeleeWeapon* CurrWeapon = Cast<AMeleeWeapon>(Weapon->GetChildActor());
	if (CurrWeapon) {
		CurrWeapon->AttackCombo(CurrWeapon->GetLightAttackData());
	}
}

void AMeleeEnemy::HeavyAttack(){
	AMeleeWeapon* CurrWeapon = Cast<AMeleeWeapon>(Weapon->GetChildActor());
	if (CurrWeapon) {
		CurrWeapon->AttackCombo(CurrWeapon->GetHeavyAttackData());
	}
}

void AMeleeEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}
