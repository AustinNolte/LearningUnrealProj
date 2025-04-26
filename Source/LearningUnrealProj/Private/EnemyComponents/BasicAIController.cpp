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

void ABasicAiController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus){

	if (Stimulus.WasSuccessfullySensed())
	{
		StopMovement();
		Blackboard->SetValueAsObject("Player", Actor);
	}
	else
	{
		Blackboard->ClearValue("Player");
	}
}
