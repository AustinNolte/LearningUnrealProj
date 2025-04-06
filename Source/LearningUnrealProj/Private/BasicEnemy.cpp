#include "BasicEnemy.h"

// Sets default values
ABasicEnemy::ABasicEnemy() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Adjusting Size of Physics Component
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	// setting overlap query of capsule of enemy
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap); // Overlap with projectiles
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}
// Using Kismet GameplayStatistics functions for damage
float ABasicEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	
	health -= DamageAmount;
	
	UE_LOG(LogTemp, Log, TEXT("Enemy took damage! Health remaining: %f"), health);

	if (health <= 0) {
		Die();
	}

	return DamageAmount;
}

void ABasicEnemy::Die() {

	UE_LOG(LogTemp, Log, TEXT("Enemy Died!"));

	AFPS_GameModeBase* GameMode = Cast<AFPS_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode){
		GameMode->IncreaseKillCount();
	}
	Destroy();
}
