#include "MainCanvas.h"

UMainCanvas::UMainCanvas(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UMainCanvas::NativeConstruct(){
	Super::NativeConstruct();
}

/*------------- Health Bar Section ---------------- */

void UMainCanvas::UpdateHealth(float Value){
	HealthBarWidget->UpdateHealth(Value);
}

void UMainCanvas::ResetHealth(){
	HealthBarWidget->ResetHealth();
}

/*------------- Stamina Bar Section ---------------- */

void UMainCanvas::UpdateStamina(float Value){
	StaminaBarWidget->UpdateStamina(Value);
}

void UMainCanvas::ResetStamina(){
	StaminaBarWidget->ResetStamina();
}
