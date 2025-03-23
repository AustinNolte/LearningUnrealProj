#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Interactable.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FirstPersonCharacter.h"
#include "Weapon.h"
#include "WeaponPickup.generated.h"

class USphereComponent; 
class USkeletalMeshComponent;
class AWeapon;

UCLASS()
class LEARNINGUNREALPROJ_API AWeaponPickup : public AInteractable{
	
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	// Sets default values for this actor's properties
	AWeaponPickup();

	virtual void Interact(AActor* InteractingActor) override;
};