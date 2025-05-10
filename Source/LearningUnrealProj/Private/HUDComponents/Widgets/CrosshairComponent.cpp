// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDComponents/Widgets/CrosshairComponent.h"

UCrosshairComponent::UCrosshairComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){

}

void UCrosshairComponent::NativeConstruct(){
    Super::NativeConstruct();

    if (CrosshairMaterial && CrosshairImage){

        CrosshairDynamicMaterial = UMaterialInstanceDynamic::Create(CrosshairMaterial, this);
        CrosshairImage->SetBrushFromMaterial(CrosshairDynamicMaterial);
    }

    if (ReloadAnimationMaterial && ReloadAnimationImage) {

        ReloadAnimationDynamicMaterial = UMaterialInstanceDynamic::Create(ReloadAnimationMaterial, this);
        ReloadAnimationImage->SetBrushFromMaterial(ReloadAnimationDynamicMaterial);
        
    }

    // Hitmarker is not dynamic, no need to make a dynamic material
    if (HitMarkerImage && HitMarkerMaterial) {
        HitMarkerImage->SetBrushFromMaterial(HitMarkerMaterial);
        HitMarkerImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UCrosshairComponent::SetCrosshairThickness(float Value){
    if (CrosshairDynamicMaterial){
        CrosshairDynamicMaterial->SetScalarParameterValue("Thickness", Value);
    }
}

void UCrosshairComponent::SetCrosshairGap(float Value){
    if (CrosshairDynamicMaterial) {
        CrosshairDynamicMaterial->SetScalarParameterValue("Gap", Value);
    }
}

void UCrosshairComponent::SetCrosshairLen(float Value){
    if (CrosshairDynamicMaterial) {
        CrosshairDynamicMaterial->SetScalarParameterValue("Length", Value);
    }
}

void UCrosshairComponent::SetCrosshairDotSize(float Value){
    if (CrosshairDynamicMaterial) {
        CrosshairDynamicMaterial->SetScalarParameterValue("DotSize", Value);
    }
}

void UCrosshairComponent::SetCrosshairColor(FLinearColor Color){
    FVector4 ColorVec = FVector4(Color.R, Color.G, Color.B, Color.A);

    if (CrosshairDynamicMaterial) {
        CrosshairDynamicMaterial->SetVectorParameterValue("Color", ColorVec);
    }
}

void UCrosshairComponent::SetCrosshairType(ECrossHairType CrosshairType){
    if (CrosshairDynamicMaterial) {
        switch (CrosshairType) {
            case ECrossHairType::Dot: CrosshairDynamicMaterial->SetScalarParameterValue("CrosshairType", 0); break;
            case ECrossHairType::Circle: CrosshairDynamicMaterial->SetScalarParameterValue("CrosshairType", 1); break;
            case ECrossHairType::Cross: CrosshairDynamicMaterial->SetScalarParameterValue("CrosshairType", 2); break;
            default: CrosshairDynamicMaterial->SetScalarParameterValue("CrossahairType", 2); break; // default to cross as its the usual one most people expect
        }
    }
}

void UCrosshairComponent::SetReloadPercentage(float Value){
    if (ReloadAnimationDynamicMaterial) {
        ReloadAnimationDynamicMaterial->SetScalarParameterValue("Percent", Value);
    }
}

void UCrosshairComponent::ToggleReloadVisibility() {
    if (ReloadAnimationImage) {
        if (ReloadAnimationImage->GetVisibility() == ESlateVisibility::Visible) {
            ReloadAnimationImage->SetVisibility(ESlateVisibility::Hidden);
        }
        else if(ReloadAnimationImage->GetVisibility() == ESlateVisibility::Hidden) {
            ReloadAnimationImage->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UCrosshairComponent::ToggleHitMarker(){
    if (HitMarkerImage) {
        HitMarkerImage->SetVisibility(ESlateVisibility::Visible);
        GetWorld()->GetTimerManager().SetTimer(
            HitMarkerTimer,
            this,
            &UCrosshairComponent::HitMarkerHelper,
            0.1f,
            false
        );
    }
}

void UCrosshairComponent::HitMarkerHelper() {
    if (HitMarkerImage) {
        HitMarkerImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
