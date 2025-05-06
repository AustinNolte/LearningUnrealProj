#include "HUDComponents/Widgets/StaminaBarWidget.h"

UStaminaBarWidget::UStaminaBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UStaminaBarWidget::NativeConstruct() {
	Super::NativeConstruct();

}

void UStaminaBarWidget::UpdateStamina(float Value) {

	if (StaminaBar) {
		StaminaBar->SetPercent(Value);
	}
}

void UStaminaBarWidget::ResetStamina() {

	if (StaminaBar) {
		StaminaBar->SetPercent(100.0f);
	}
}
