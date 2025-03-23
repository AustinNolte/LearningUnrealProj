// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_GameModeBase.h"

void AFPS_GameModeBase::StartPlay() {

	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Hello World From FPS_GameModeBase"));
}