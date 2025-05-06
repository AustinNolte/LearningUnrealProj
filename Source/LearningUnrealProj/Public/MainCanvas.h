#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HUDComponents/Widgets/HealthBarWidget.h"
#include "HUDComponents/Widgets/StaminaBarWidget.h"

#include "Components/CanvasPanel.h"
#include "MainCanvas.generated.h"

class UHealthBarWidget;
class UStaminaBarWidget;

UCLASS()
class LEARNINGUNREALPROJ_API UMainCanvas : public UUserWidget{

	GENERATED_BODY()

public:

	UMainCanvas(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MainCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHealthBarWidget* HealthBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UStaminaBarWidget* StaminaBarWidget;


public:

	/*------------- Health Bar Section ---------------- */
	

	/* Takes percent of health left (CurrentHealth/MAX_HEALTH) */
	void UpdateHealth(float Value);

	/* Resets Health to 100% */
	void ResetHealth(); 
	 

	/*------------- Stamina Bar Section ---------------- */

	/* Takes percent of Stamina left (CurrentStamina/MAX_STAMINA) */
	void UpdateStamina(float Value);

	/* Resets Stamina to 100% */
	void ResetStamina();
};
