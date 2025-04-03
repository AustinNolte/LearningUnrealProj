#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Interactable.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "FirstPersonCharacter.h"
#include "Weapon.h"
#include "WeaponPickup.generated.h"

class USphereComponent; 
class USkeletalMeshComponent;
class UTextRenderComponent;
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
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* DisplayText;
	
	// Sets default values for this actor's properties
	AWeaponPickup();

	virtual void BeginPlay() override;

	virtual void Interact(AActor* InteractingActor) override;

	virtual void Tick(float DeltaTime) override;
		
protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};