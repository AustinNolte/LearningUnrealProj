#include "Portal.h"

APortal::APortal(){

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractableArea")); // name object
	Sphere->SetSphereRadius(100.0f); // set size
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // set to only check for overlap, not actually collide
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore); // ignore collision channels and masks
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // check overlap for pawns
	
	RootComponent = Sphere;

	DisplayText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("No World"));
	DisplayText->SetHorizontalAlignment(EHTA_Center);
	DisplayText->SetVerticalAlignment(EVRTA_TextCenter);
	DisplayText->SetWorldSize(50.0f);
	DisplayText->SetTextRenderColor(FColor::Magenta);

	DisplayText->SetupAttachment(RootComponent);

	DisplayText->SetVisibility(false);
}

void APortal::BeginPlay() {
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APortal::OnOverlapEnd);

	if (WorldName != "") {
		DisplayText->SetText(FText::FromString(WorldName.ToString() + "\n Press [E] to teleport"));
	} 
	else {
		DisplayText->SetText(FText::FromString("World Not Set"));
	}
}

void APortal::Interact_Implementation(AActor* InteractingActor){
	
	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(InteractingActor);
	if (Player && WorldName != "") {

		UGameplayStatics::OpenLevel(GetWorld(), WorldName);
	}
}


void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(OtherActor);

	if (Player) {
		//UE_LOG(LogTemp, Warning, TEXT("Overlap Begun with: %s"), *Player->GetName());
	
		DisplayText->SetVisibility(true);
	}	
}

void APortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(OtherActor);

	if (Player) {
		//UE_LOG(LogTemp, Warning, TEXT("Overlap Ended with: %s"), *Player->GetName());
	
		DisplayText->SetVisibility(false);
	}
}

void APortal::Tick(float DeltaTime) {
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
