#include "EnemyComponents/BasicAiController.h"

ABasicAiController::ABasicAiController() {

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABasicAiController::OnTargetPerceptionUpdate);

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));

}

// Called when the game starts or when spawned
void ABasicAiController::BeginPlay() {
	Super::BeginPlay();


}

void ABasicAiController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Sitmulus){

}
