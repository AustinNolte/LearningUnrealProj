#include "WeaponComponents/Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FirstPersonCharacter.h"
#include "HUDComponents/FPS_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "BasicEnemy.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure object hirearchy

	// configure sphere as the simple collision object
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SphereComponent->InitSphereRadius(0.5f);
	SphereComponent->BodyInstance.SetCollisionProfileName("Projectile");

	// Don't allow players to walk on it
	SphereComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	SphereComponent->CanCharacterStepUpOn = ECB_No;

	// want collision object to be root component as it is the object moving and interacting with rest of scene.
	RootComponent = SphereComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	// disabling physics for projectile so it floats
	StaticMeshComponent->SetSimulatePhysics(false);

	// Set collision to overlap (instead of block)
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Only detects overlaps, no physical collision
	StaticMeshComponent->SetCollisionObjectType(ECC_WorldDynamic); // Set it as a dynamic object
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignore all collisions

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovement->UpdatedComponent = SphereComponent;

	// Speed shouldn't get larger than the inital speed (Air Resistance etc)
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;

	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false; // bullets shouldn't bounce

	// Projectile lives for 3 seconds by default
	timeToLive = 3.0f;

	// deafault damage value, adjust in blueprint for fine tuning
	damage = 1;
}

void AProjectile::BeginPlay() {

	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);

}

// Called every frame
void AProjectile::Tick(float DeltaTime) {

	timeToLive -= DeltaTime;

	if (timeToLive <= 0.0f) {
		Destroy();
		return;
	}
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	//first check if it is an enemy it is hitting
	ABasicEnemy* EnemyHit = Cast<ABasicEnemy>(OtherActor);
	if (EnemyHit) {
		UGameplayStatics::ApplyDamage(EnemyHit, damage, GetInstigatorController(), this, UDamageType::StaticClass());

		// play hit marker section
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // single player therefore 0th index

		AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(PlayerPawn);
		if (Player) {
			AFPS_HUD* HUD = Player->GetHud();
			if (HUD) {
				HUD->ToggleHitMarker();
			}
		}


		Destroy();
	}
}