#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicAiController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class LEARNINGUNREALPROJ_API ABasicAiController : public AAIController {

	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* behaviorTree;

public:
	// Sets default values for this controller's properties
	ABasicAiController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
