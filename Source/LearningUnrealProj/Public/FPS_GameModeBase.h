// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "FPS_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALPROJ_API AFPS_GameModeBase : public AGameModeBase{

	GENERATED_BODY()
	
	virtual void StartPlay() override;


public:

	// keeping track of players kill count for events
	int32 KillCount;

	UFUNCTION(BlueprintPure, Category = "Kill Count")
	FORCEINLINE int GetKillCount() const { return KillCount; }

	UFUNCTION(BlueprintCallable, Category = "Kill Count")
	FORCEINLINE void ResetKillCount() { KillCount = 0; }

	UFUNCTION(BlueprintCallable, Category = "Kill Count")
	FORCEINLINE void IncreaseKillCount() { KillCount++; }

};

