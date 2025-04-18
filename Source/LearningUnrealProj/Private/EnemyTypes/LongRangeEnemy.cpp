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
}


void ALongRangeEnemy::FireWeapon(){
	UE_LOG(LogTemp, Warning, TEXT("CanFire: %d"), canFire);

	if (Weapon && canFire) {

		UE_LOG(LogTemp, Warning, TEXT("Here in FireWeapon"));
		FVector3d endPoint = Target->GetActorLocation();
		FVector3d Direction = endPoint - (Cast<AEnemyWeapon>(Weapon->GetChildActor())->GetSkeleton()->GetSocketLocation("ProjectileSpawn"));

		Direction.Normalize();
		UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString());
		Cast<AEnemyWeapon>(Weapon->GetChildActor())->Fire(Direction);
		canFire = false;
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

