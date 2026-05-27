
#include "UTask_RunAwayFromZombie.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombies/BaseZombie.h"
#include "Survivor/SurvivorPawn.h"


UUTask_RunAwayFromZombie::UUTask_RunAwayFromZombie()
{
	NodeName = "Run Away From Zombie";
}

EBTNodeResult::Type UUTask_RunAwayFromZombie ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	//get all var needed
	AAIController* AIController = OwnerComponent.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* Survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!Survivor) return EBTNodeResult::Failed;
	
	UBlackboardComponent* Blackboard = OwnerComponent.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;
	//---------------------------------------------------
	
	ABaseZombie* Zombie = Cast<ABaseZombie>(Blackboard->GetValueAsObject(FName("TargetZombie"))); //get from blackboard
	
	if (!Zombie) return EBTNodeResult::Failed; //security, but there should always be a zombie target (goes thorugh decorator)


	FVector playerLocation = Survivor->GetActorLocation();
	FVector zombieLocaion = Zombie->GetActorLocation();
	FVector direction = (playerLocation - zombieLocaion).GetSafeNormal();
    
	//target to run towards
	FVector EscapeTargetLocation = playerLocation + (direction * 1900.0f);
	
	TArray<FVector> PathPoints = Survivor->CalculatePath(EscapeTargetLocation); //BLESSS
	
	if (PathPoints.Num() != 0)
	{
		Survivor->StartRunning();
		AIController->MoveToLocation(PathPoints[1], 50.0f, false, true, true, true, 0, true);
		return EBTNodeResult::Succeeded; 
		
	}
	
	return EBTNodeResult::Failed;
}