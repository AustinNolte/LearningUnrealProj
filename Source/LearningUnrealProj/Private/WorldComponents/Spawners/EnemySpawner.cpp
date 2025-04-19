#include "WorldComponents/Spawners/EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly); // mesh should only block objects from passing through
	Mesh->SetCollisionObjectType(ECC_WorldStatic); // mesh should be static
	Mesh->SetCollisionResponseToAllChannels(ECR_Block); // Block all collisions

	RootComponent = Mesh;

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleSystem"));
	NiagaraComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay(){
	Super::BeginPlay();
	
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AEnemySpawner::WaveGenerator(){
	FWaveData CurrentWaveData = Waves[CurrentWaveIndex];
	if (CurrentWaveState == EWaveState::Idle) {
		// Do nothing - waiting for wave to start
	}
	else if (CurrentWaveState == EWaveState::Spawning) {
		if (EnemiesSpawnedCurrentWave < Waves[CurrentWaveIndex].BaseEnemyCount) {

			++EnemiesSpawnedCurrentWave;	
			TSubclassOf<ABasicEnemy> EnemyToSpawn = SelectEnemy(Waves[CurrentWaveIndex]);
			SpawnEnemy(EnemyToSpawn);
			UE_LOG(LogTemp, Log, TEXT("EnemiesSpawnedCurrentWave: %d"), EnemiesSpawnedCurrentWave);

		}
		else {

			CurrentWaveState = EWaveState::Waiting;

		}
	}
	else if (CurrentWaveState == EWaveState::Waiting) {
		if (EnemiesKilledDuringWave >= EnemiesSpawnedCurrentWave) {
			CurrentWaveState = EWaveState::Completed;
		}
	}
	else if (CurrentWaveState == EWaveState::Completed) {

		++CurrentWaveIndex;
		CurrentWaveState = EWaveState::Idle;

		if (CurrentWaveIndex < Waves.Num()) {
			
			EnemiesKilledDuringWave = 0;
			EnemiesSpawnedCurrentWave = 0;
			WaveGenerator();
		}
		else if (CurrentWaveIndex >= Waves.Num()) {
			Destroy();
		}
	}
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<ABasicEnemy> EnemyType){
	FNavLocation SpawnLocation;
	FVector Origin = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
	NavSystem->GetRandomReachablePointInRadius(Origin, SpawnRadius, SpawnLocation, nullptr, nullptr);

	float CapsuleHalfHeight = EnemyType.GetDefaultObject()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	
	FVector FinalSpawnLocation = SpawnLocation.Location + FVector(0.f, 0.f, CapsuleHalfHeight);
	FRotator SpawnRotation = FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f);
	UE_LOG(LogTemp, Log, TEXT("Random Spawn Location: %s"), *FinalSpawnLocation.ToString());
	
	
	ABasicEnemy* Enemy = GetWorld()->SpawnActor<ABasicEnemy>(EnemyType.Get(), FinalSpawnLocation, SpawnRotation);
	if (Enemy) {

		// allow enemy to be tracked for death
		Enemy->EnemyDied.AddDynamic(this, &AEnemySpawner::OnEnemyKilled);

		UE_LOG(LogTemp, Log, TEXT("BoundDelegate"));
	}
}

void AEnemySpawner::OnEnemyKilled(int8 Value){
	++EnemiesKilledDuringWave;
	UE_LOG(LogTemp, Log, TEXT("EnemiesKilledDuringWave: %d"), EnemiesKilledDuringWave);
}

TSubclassOf<ABasicEnemy> AEnemySpawner::SelectEnemy(FWaveData CurrentWaveData){
	
	if (EnemySpawnDataTable) {
		TArray<FEnemySpawnData*> AllRows;
		EnemySpawnDataTable->GetAllRows(TEXT("EnemySpawnData"), AllRows);

		float TotalWeight = 0.f;
		for (const FEnemySpawnData* Row : AllRows) {
			if (CurrentWaveData.EnemyTypes.Contains(Row->EnemyClass)) {
				//UE_LOG(LogTemp,Warning, TEXT("EnemyClass: %s"), *Row->EnemyClass.GetDefaultObject()->GetName())
				TotalWeight += Row->SpawnWeight;
			}
		}

		// picking a random float betwene 0 and TotalWeight
		float RandomSelection = FMath::RandRange(0.f, TotalWeight);
		
		// reseting total weight to use again
		TotalWeight = 0.f;

		for (const FEnemySpawnData* Row : AllRows) {
			if (CurrentWaveData.EnemyTypes.Contains(Row->EnemyClass)) {
				TotalWeight += Row->SpawnWeight;
			}

			if (RandomSelection <= TotalWeight) {
				return Row->EnemyClass;
			}
		}
	}
	return nullptr;
}

void AEnemySpawner::StartWave() {
	if (CurrentWaveState == EWaveState::Idle || CurrentWaveState == EWaveState::Completed) {

		CurrentWaveState = EWaveState::Spawning;
		GetWorldTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&AEnemySpawner::WaveGenerator,
			Waves[CurrentWaveIndex].SpawnRate,
			true
		);
	}
}

