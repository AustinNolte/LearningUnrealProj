#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPS_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "BasicEnemy.generated.h"

class USkeletalMeshComponent;



UCLASS()
class LEARNINGUNREALPROJ_API ABasicEnemy : public ACharacter{
	
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float health; // health of enemy

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float damage; // damage per attack

	// Sets default values for this pawn's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// taking damage and handling death
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die();

};
