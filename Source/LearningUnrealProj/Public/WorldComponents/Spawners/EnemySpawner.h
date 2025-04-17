// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "DataTables/EnemySpawnData.h"
#include "NavigationSystem.h"
#include "EnemySpawner.generated.h"

class UStaticMeshComponent;
class UNigaraComponent;

// individual wave data
USTRUCT(BlueprintType)
struct FWaveData {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
	int32 BaseEnemyCount = 10;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
	float SpawnRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
	TArray<TSubclassOf<ABasicEnemy>> EnemyTypes;

};

// handle state of current spawning
UENUM(BlueprintType)
enum class EWaveState : uint8 {

	Idle		UMETA(DisplayName = "Idle"),		// Not doing anything
	Spawning	UMETA(DisplayName = "Spawning"),	// Currently Spawning Enemies
	Waiting		UMETA(DisplayName = "Waiting"),		// Waiting for wave to end
	Completed	UMETA(DisplayNAme = "Completed")
};

UCLASS()
class LEARNINGUNREALPROJ_API AEnemySpawner : public AActor{

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	TArray<FWaveData> Waves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyData")
	UDataTable* EnemySpawnDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyData")
	float SpawnRadius;
	
	UPROPERTY(BluePrintReadWrite)
	EWaveState CurrentWaveState = EWaveState::Idle;
	
	UFUNCTION(BlueprintCallable)
	void StartWave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 EnemiesKilledDuringWave = 0;

	// wave control flow 
	int32 EnemiesSpawnedCurrentWave;
	FORCEINLINE void ResetEnemiesSpawnedCounter(){ EnemiesSpawnedCurrentWave = 0; }
	FORCEINLINE void IncrementEnemiesSpawnedCounter() { ++EnemiesSpawnedCurrentWave; }

	

	FTimerHandle SpawnTimerHandle;

	UNavigationSystemV1* NavSystem;

	int32 CurrentWaveIndex = 0;

	// randomize what enemy to spawn
	TSubclassOf<ABasicEnemy> SelectEnemy(FWaveData CurrentWaveData);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// enemy spawning functions
	FORCEINLINE void ResetEnemiesKillCounter() { EnemiesKilledDuringWave = 0; }
	
	FORCEINLINE void IncrementEnemiesKillCounter() { ++EnemiesKilledDuringWave;  }

	void WaveGenerator();
	
	void SpawnEnemy(TSubclassOf<ABasicEnemy> EnemyType);

	UFUNCTION()
	void OnEnemyKilled(int8 Value);

	};
