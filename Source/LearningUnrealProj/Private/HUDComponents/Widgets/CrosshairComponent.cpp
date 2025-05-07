// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDComponents/Widgets/CrosshairComponent.h"

UCrosshairComponent::UCrosshairComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){

}

void UCrosshairComponent::NativeConstruct(){
    Super::NativeConstruct();

    if (CrosshairMaterial && CrosshairImage){

        DynamicMaterial = UMaterialInstanceDynamic::Create(CrosshairMaterial, this);
        CrosshairImage->SetBrushFromMaterial(DynamicMaterial);
    }
}

void UCrosshairComponent::SetCrosshairThickness(float Value){
    if (DynamicMaterial){

        DynamicMaterial->SetScalarParameterValue("Thickness", Value);
    }

}

void UCrosshairComponent::SetCrosshairGap(float Value){
    if (DynamicMaterial) {

        DynamicMaterial->SetScalarParameterValue("Gap", Value);
    }
}

void UCrosshairComponent::SetCrosshairLen(float Value){
    if (DynamicMaterial) {

        DynamicMaterial->SetScalarParameterValue("Length", Value);
    }
}

void UCrosshairComponent::SetCrosshairColor(FLinearColor Color){
    FVector4 ColorVec = FVector4(Color.R, Color.G, Color.B, Color.A);
    if (DynamicMaterial) {

        DynamicMaterial->SetVectorParameterValue("Color", ColorVec);
    }
}

void UCrosshairComponent::SetCrosshairType(ECrossHairType CrosshairType){

}
