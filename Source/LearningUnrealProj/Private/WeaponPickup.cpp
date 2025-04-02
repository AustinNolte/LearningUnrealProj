// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include <Kismet/GameplayStatics.h>

AWeaponPickup::AWeaponPickup() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	// disabling physics for weapon so it floats
	SkeletalMesh->SetSimulatePhysics(false);

	// Set collision to overlap (instead of block)
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Only detects overlaps, no physical collision
	SkeletalMesh->SetCollisionObjectType(ECC_WorldDynamic); // Set it as a dynamic object
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore all collisions

	// making the mesh the root component
	RootComponent = SkeletalMesh;


	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpArea")); // name object
	Sphere->SetupAttachment(RootComponent); // attach to root
	Sphere->SetSphereRadius(100.0f); // set size
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // set to only check for overlap, not actually collide
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore); // ignore collision channels and masks
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // check overlap for pawns

	DisplayText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("No World"));
	DisplayText->SetHorizontalAlignment(EHTA_Center);
	DisplayText->SetVerticalAlignment(EVRTA_TextCenter);
	DisplayText->SetWorldSize(50.0f);
	DisplayText->SetTextRenderColor(FColor::Magenta);

	DisplayText->SetupAttachment(Sphere);

	DisplayText->SetVisibility(false);
}

void AWeaponPickup::BeginPlay() {
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AWeaponPickup::OnOverlapEnd);

	AWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, GetActorTransform());
	FString WeaponName = SpawnedWeapon->GetWeaponName();
	SpawnedWeapon->Destroy();

	if (WeaponName != "") {
		DisplayText->SetText(FText::FromString("Press[E] to pickup\n" + WeaponName));
	} 
	else {
		DisplayText->SetText(FText::FromString("Press [E] to pickup"));
	}
}


void AWeaponPickup::Interact(AActor* InteractingActor) {

	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(InteractingActor);
	if (Player && WeaponClass) {
		// Spawn the actual weapon
		AWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, GetActorTransform());

		if (SpawnedWeapon) {
			// Give weapon to player
			Player->addWeapon(SpawnedWeapon);
		}

		// Destroy the pickup after use
		Destroy();
	}
}
void AWeaponPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(OtherActor);

	if (Player) {
		//UE_LOG(LogTemp, Warning, TEXT("Overlap Begun with: %s"), *Player->GetName());
	
		DisplayText->SetVisibility(true);
	}	
}

void AWeaponPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(OtherActor);

	if (Player) {
		//UE_LOG(LogTemp, Warning, TEXT("Overlap Ended with: %s"), *Player->GetName());
	
		DisplayText->SetVisibility(false);
	}
}

void AWeaponPickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (DisplayText->IsVisible()) {
		
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController) {
			FVector Direction = PlayerController->GetPawn()->GetActorLocation() - DisplayText->GetComponentLocation();

			FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

			DisplayText->SetWorldRotation(FMath::RInterpTo(DisplayText->GetComponentRotation(), NewRotation, DeltaTime, 10.0f));
		}
	}
}

