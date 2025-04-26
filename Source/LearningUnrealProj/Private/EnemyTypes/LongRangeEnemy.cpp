#include "EnemyTypes/LongRangeEnemy.h"

ALongRangeEnemy::ALongRangeEnemy() {
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponComponent"));

	// Attach to mesh at socket
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

}

void ALongRangeEnemy::BeginPlay() {
	Super::BeginPlay();

	if (WeaponClass){
		Weapon->SetChildActorClass(WeaponClass);
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Target = Cast<AFirstPersonCharacter>(PlayerCharacter);

	URangedEnemyAnimInstance* AnimInstance = Cast<URangedEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance) {
		AnimationInstance = AnimInstance;
	}
}


void ALongRangeEnemy::FireWeapon(){

	if (Weapon && canFire) {

		FVector3d endPoint = Target->GetActorLocation();
		FVector3d Direction = endPoint - (Cast<AEnemyWeapon>(Weapon->GetChildActor())->GetSkeleton()->GetSocketLocation("ProjectileSpawn"));

		Direction.Normalize();
		Cast<AEnemyWeapon>(Weapon->GetChildActor())->Fire(Direction); 

		if (AnimationInstance) {
			AnimationInstance->PlayFireMontage();
		}

		canFire = false;
		timeSinceLastFire = 0.0f;
	}
}

void ALongRangeEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (Weapon) {	
		
		timeSinceLastFire += DeltaTime;
		if (timeSinceLastFire >= Cast<AEnemyWeapon>(Weapon->GetChildActor())->GetFireRate() && !canFire) {
			canFire = true;
		}
	}
}

