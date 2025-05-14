#include "MeleeWeapon.h"
#include "CharacterComponents/MeleePlayerAnimInstance.h"
#include "ThirdPersonCharacter.h"


// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay(){

	Super::BeginPlay();

	// Collision for weapon should only be set when swinging
	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HurtBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnOverlapBegin);

}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AMeleeWeapon::EnableHurtBox() {
	HurtBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::DisableHurtBox() {
	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

int AMeleeWeapon::GetCurrentAttackIndex() {
	if (bWantsToCombo) {
		return CurrentAttackIndex - 1;
	}
	else
		return CurrentAttackIndex;
}

/*
*
* Stamina Can be negative, this is to allow for a punishment of using too much as it will take longer to get to a positive number again
*
*/

void AMeleeWeapon::AttackCombo(FAttackData Data) {
	if (bAttacking && !bWantsToCombo) {
		bWantsToCombo = true;
		CurrentAttackIndex++;
	}
	if (PlayerOwner) {
		if (PlayerOwner->Stamina > 0 && CurrentAttackIndex < Data.StaminaPerAttack.Num() && !bWantsToCombo) {
			PlayerOwner->Stamina -= Data.StaminaPerAttack[CurrentAttackIndex];
			AFPS_HUD* HUD = PlayerOwner->GetHud();
			if (HUD) {
				HUD->UpdateStamina(PlayerOwner->Stamina/PlayerOwner->MAX_STAMINA);
			}
			PlayerOwner->StartStaminaRegenDelay();
		}
		else {	
			bAttacking = false;
			return;
		}
	}
	if (!bAttacking) {
		CurrentAttackData = Data;
		AnimInstance->PlayMontage(Data.AttackMontages);
		bAttacking = true;
		if (PlayerOwner) {
			if (PlayerOwner->IsStaminaRegen()) {
				PlayerOwner->StopStaminaRegen();
			}
		}
	}
}

void AMeleeWeapon::EnableComboWindow() {
	bEnemyHitDuringAttack = false;
	bWantsToCombo = false;
}

void AMeleeWeapon::DisableComboWindow() {
	if (!bWantsToCombo) {
		AnimInstance->StopMontage(CurrentAttackData.AttackMontages);
		ResetAttackState();
	}
}

void AMeleeWeapon::ResetAttackState() {
	bWantsToCombo = false;
	bAttacking = false;
	bEnemyHitDuringAttack = false;
	CurrentAttackIndex = 0;
	CurrentAttackData = FAttackData();
}

// needed for last hit to ensure it hits and does correct amount of damage.
void AMeleeWeapon::LastHit() {
	bEnemyHitDuringAttack = false;
	bWantsToCombo = false;
}

void AMeleeWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (PlayerOwner) {
		if (ABasicEnemy* EnemyHit = Cast<ABasicEnemy>(OtherActor)) {

			//get damage value only if an enemy has not been hit during this attack

			if (!(bEnemyHitDuringAttack)) {
				EnableEnemyHitDuringAttack();
				float Damage = CurrentAttackData.DamagePerAttack[GetCurrentAttackIndex()];
				UGameplayStatics::ApplyDamage(EnemyHit, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

				AFPS_HUD* HUD = PlayerOwner->GetHud();
				if (HUD) {
					HUD->ToggleHitMarker();
				}

			}
		}
	}
	else if (EnemyOwner) {
		if (AThirdPersonCharacter* PlayerHit = Cast<AThirdPersonCharacter>(OtherActor)) {
			if (!(bEnemyHitDuringAttack)) {
				EnableEnemyHitDuringAttack();
				float Damage = CurrentAttackData.DamagePerAttack[GetCurrentAttackIndex()];
				UGameplayStatics::ApplyDamage(PlayerHit, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
			}
		}
	}
}