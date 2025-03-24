#include "BehaviorTree/BehaviorTree.h"
#include "EnemyComponents/BasicAiController.h"

ABasicAiController::ABasicAiController() {


}

// Called when the game starts or when spawned
void ABasicAiController::BeginPlay() {
	Super::BeginPlay();

	if (behaviorTree) {
		RunBehaviorTree(behaviorTree);
	}
}
