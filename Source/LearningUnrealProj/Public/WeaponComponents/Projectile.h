#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class LEARNINGUNREALPROJ_API AProjectile : public AActor {

	GENERATED_BODY()

public:
	/** Static mesh for projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	/** Sphere collision object */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;

	/** Projectile Movement Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	// Sets default values for this actor
	AProjectile();

	// Sets time to live, adjustable in blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectile)
	float timeToLive;

	// Sets velocity (magnitude of vector) of projectile, adjustable in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float speed;

	// Sets damage value of the projectile (magnitude of vector) of projectile, adjustable in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	float damage;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	 
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	  
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};