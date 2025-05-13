#include "CharacterComponents/PlayerUserSettings.h"

void UPlayerUserSettings::SetCrosshairGap(float Value){
	CrosshairGap = FMath::Clamp(Value, 0.0f, 10.0f);
}

void UPlayerUserSettings::SetCrosshairThickness(float Value) {
	CrosshairThickness = FMath::Clamp(Value, 0.0, 10.0);
}

void UPlayerUserSettings::SetCrosshairLen(float Value) {
	CrosshairLen = FMath::Clamp(Value, 0.0f, 10.0f);
}

void UPlayerUserSettings::SetCrosshairDotSize(float Value) {
	CrosshairDotSize = FMath::Clamp(Value, 0.2f, 5.0f);
}

void UPlayerUserSettings::SetRGBColor(FVector4 Value) {
	RGBColor.X = FMath::Clamp(Value.X, 0.0f, 255.0f);
	RGBColor.Y = FMath::Clamp(Value.Y, 0.0f, 255.0f);
	RGBColor.Z = FMath::Clamp(Value.Z, 0.0f, 255.0f);
	RGBColor.W = FMath::Clamp(Value.W, 0.0f, 255.0f);
}

void UPlayerUserSettings::SetCrosshairType(uint8 Value) {
	Value = FMath::Clamp(Value, 0, 2);
	Type = static_cast<ECrossHairType>(Value);
}

void UPlayerUserSettings::SetSensitivity(float Value){
	Sensitivity = FMath::Clamp(Value, .1f, 8.0f);
}

void UPlayerUserSettings::SetSound(float Value){
	OverallSound = FMath::Clamp(Value, 0.0f, 100.0f);
}

void UPlayerUserSettings::ApplySettings(bool bCheckForCommandLineOverrides){ 

	Super::ApplySettings(bCheckForCommandLineOverrides);

	SaveSettings();
}

UPlayerUserSettings* UPlayerUserSettings::GetPlayerUserSettings() {
	return Cast<UPlayerUserSettings>(GEngine->GetGameUserSettings());
}
