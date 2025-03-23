// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALPROJ_API AFPS_GameModeBase : public AGameModeBase{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
};
