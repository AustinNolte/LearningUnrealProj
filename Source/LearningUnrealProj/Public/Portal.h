#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "FirstPersonCharacter.h"
#include "Portal.generated.h"



class FName;
class UTextRenderComponent;
class USphereComponent;

UCLASS()
class LEARNINGUNREALPROJ_API APortal : public AInteractable{
	
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "New Level")
	FName WorldName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;
	
	UTextRenderComponent* DisplayText;

	// when player interacts swap world
	virtual void Interact(AActor* InteractingActor) override;

	// Set values when begin play happens
	virtual void BeginPlay() override;

	// Sets default values for this actor's properties
	APortal();


protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



};
