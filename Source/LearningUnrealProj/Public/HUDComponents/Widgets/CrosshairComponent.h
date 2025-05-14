#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "CrosshairComponent.generated.h"

UENUM(BlueprintType)
enum class ECrossHairType : uint8 {
	Cross	UMETA(DisplayName = "Cross"),
	Dot		UMETA(DisplayName = "Dot"),
	Circle	UMETA(DisplayName = "Circle")
};

class UImage;
class UMaterialInstanceDynamic;
class USoundBase;


UCLASS()
class LEARNINGUNREALPROJ_API UCrosshairComponent : public UUserWidget{

	GENERATED_BODY()

public:

	UCrosshairComponent(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	/* Crosshair thickeness, in percent of screen space */
	UFUNCTION(BlueprintCallable)
	void SetCrosshairThickness(float Value);

	/* Crosshair Gap, in percent of screen space */
	UFUNCTION(BlueprintCallable)

	void SetCrosshairGap(float Value);

	/* CrosshairLen if crosshair type, in percent of screen space */
	UFUNCTION(BlueprintCallable)
	void SetCrosshairLen(float Value);

	/* Corsshair Dot size if crosshair type is dot */
	UFUNCTION(BlueprintCallable)
	void SetCrosshairDotSize(float Value);

	/* Color of crosshair in format of (R,G,B,A) */
	UFUNCTION(BlueprintCallable)
	void SetCrosshairColor(FLinearColor Color);

	/* Set CrosshairType from enum of ECrossHairType */
	UFUNCTION(BlueprintCallable)
	void SetCrosshairType(ECrossHairType CrosshairType);
	
	/* Set Reload Animation Percentage, Value should be 0-1 */
	UFUNCTION(BlueprintCallable)
	void SetReloadPercentage(float Value);

	/* Toggle Visibility of reload circle */
	UFUNCTION(BlueprintCallable)
	void ToggleReloadVisibility();

	/* Toggle hitmarkers */
	void ToggleHitMarker();

	/* Toggle FPS Mode */
	void ToggleFPSMode();

	/* Toggle TPS Mode*/
	void ToggleTPSMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CrosshairImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	UMaterialInterface* CrosshairMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ReloadAnimationImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	UMaterialInterface* ReloadAnimationMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(BindWidget))
	UImage* HitMarkerImage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Crosshair")
	UMaterialInterface* HitMarkerMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitmarker Sound")
	USoundBase* HitMarkerSound;


private:
	UMaterialInstanceDynamic* CrosshairDynamicMaterial;
	UMaterialInstanceDynamic* ReloadAnimationDynamicMaterial;

	void HitMarkerHelper();
	FTimerHandle HitMarkerTimer;
};
