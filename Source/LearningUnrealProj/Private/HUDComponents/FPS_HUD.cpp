#include "HUDComponents/FPS_HUD.h"

AFPS_HUD::AFPS_HUD(){}

void AFPS_HUD::DrawHUD(){
	Super::DrawHUD();

	DrawCrosshair();
	
}

void AFPS_HUD::BeginPlay(){
	Super::BeginPlay();

	if (MainGameUIClass && GetWorld()) {
		
		MainGameCanvas = CreateWidget<UMainCanvas>(GetWorld(), MainGameUIClass);
		if (MainGameCanvas) {
			MainGameCanvas->AddToViewport();
		}
	}
}

void AFPS_HUD::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
}

/*------------- Health Bar Section ---------------- */

void AFPS_HUD::UpdateHealth(float Value){

	if (MainGameCanvas) {
		MainGameCanvas->UpdateHealth(Value);
	}

}

void AFPS_HUD::ResetHealth(){

	if (MainGameCanvas) {
		MainGameCanvas->ResetHealth();
	}
}

/*------------- Stamina Bar Section ---------------- */


void AFPS_HUD::UpdateStamina(float Value) {

	if (MainGameCanvas) {
		MainGameCanvas->UpdateStamina(Value);
	}
}

void AFPS_HUD::ResetStamina() {

	if (MainGameCanvas) {
		MainGameCanvas->ResetStamina();
	}
}

/*------------- Ammo and Display Section ---------------- */

void AFPS_HUD::UpdateAmmo(int32 CurrAmmo, int32 MAX_AMMO) {
	MainGameCanvas->UpdateAmmo(CurrAmmo, MAX_AMMO);
}

void AFPS_HUD::ResetAmmo(int32 MAX_AMMO) {
	MainGameCanvas->ResetAmmo(MAX_AMMO);
}

void AFPS_HUD::ChangeWeapon(AWeapon* NewWeapon) {
	MainGameCanvas->ChangeWeapon(NewWeapon);
}


/*------------- Crosshair Section ---------------- */

void AFPS_HUD::DrawCrosshair() {

	// Draw four lines
	if (Canvas) {
		// get center screen
		float CenterX = Canvas->ClipX / 2;
		float CenterY = Canvas->ClipY / 2;

		// Scale should be uniform from DPIScale of viewport
		float UniformScale = PlayerOwner->GetLocalPlayer()->ViewportClient->GetDPIScale();

		float ScaledGap = CrosshairGap / UniformScale;

		float ScaledLen = CrosshairLen / UniformScale;
		
		// Start X 
		float LeftLineStart = CenterX - (ScaledGap / 2);
		float RightLineStart = CenterX + (ScaledGap / 2);
				
		// End X
		float LeftLineEnd = CenterX - (ScaledGap / 2) - ScaledLen;
		float RightLineEnd = CenterX + (ScaledGap / 2) + ScaledLen;

		 
		// Start Y 
		float BottomLineStart = CenterY + (ScaledGap / 2);
		float TopLineStart = CenterY - (ScaledGap / 2);

		// End Y
		float BottomLineEnd = CenterY + (ScaledGap / 2) + ScaledLen;
		float TopLineEnd = CenterY - (ScaledGap / 2) - ScaledLen;

		FLinearColor Color = FLinearColor(RGBColor/255.0f);
		// left line
		DrawLine(LeftLineStart, CenterY, LeftLineEnd, CenterY, Color, CrosshairThickness);
		// right line
		DrawLine(RightLineStart, CenterY, RightLineEnd, CenterY, Color, CrosshairThickness);
		// top line
		DrawLine(CenterX, TopLineStart, CenterX, TopLineEnd, Color, CrosshairThickness);
		// bottom line
		DrawLine(CenterX, BottomLineStart, CenterX, BottomLineEnd, Color, CrosshairThickness);
	} 
}
