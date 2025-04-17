// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemySpawnData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemySpawnData : public FTableRowBase {
	
	GENERATED_BODY()

public:
	// class of enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawn Data")
	TSubclassOf<class ABasicEnemy> EnemyClass;

	// spawning weight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawn Data")
	float SpawnWeight;
};
