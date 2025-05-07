#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CrosshairComponent.generated.h"

UENUM(BlueprintType)
enum class ECrossHairType : uint8 {
	Cross	UMETA(DisplayName = "Cross"),
	Dot		UMETA(DisplayName = "Dot"),
	Circle	UMETA(DisplayName = "Circle")
};

class UImage;
class UMaterialInstanceDynamic;


UCLASS()
class LEARNINGUNREALPROJ_API UCrosshairComponent : public UUserWidget{

	GENERATED_BODY()

public:

	UCrosshairComponent(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	/* Crosshair thickeness, in percent of screen space */
	void SetCrosshairThickness(float Value);

	/* Crosshair Gap, in percent of screen space */
	void SetCrosshairGap(float Value);

	/* CrosshairLen if crosshair type, in percent of screen space */
	void SetCrosshairLen(float Value);

	/* Color of crosshair in format of (R,G,B,A) */
	void SetCrosshairColor(FLinearColor Color);

	/* Set CrosshairType from enum of ECrossHairType */
	void SetCrosshairType(ECrossHairType CrosshairType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CrosshairImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	UMaterialInterface* CrosshairMaterial;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
	
};
