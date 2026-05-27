// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_FinishHouseVisit.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "SurvivorAccessor.h"
#include "Village/House/House.h"

UUTask_FinishHouseVisit::UUTask_FinishHouseVisit()
{
	NodeName = "Finished Visiting House";
}

EBTNodeResult::Type UUTask_FinishHouseVisit ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	AAIController* AIController = OwnerComponent.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UBlackboardComponent* blackboard = OwnerComponent.GetBlackboardComponent();
	if (!blackboard) return EBTNodeResult::Failed;
	
	ASurvivorAccessor* survivorAcc = static_cast<ASurvivorAccessor*>(survivor);
	
	survivorAcc->visitedHouses.Add( Cast<AHouse>(blackboard->GetValueAsObject(FName("TargetHouse"))));
	blackboard->SetValueAsObject(FName("TargetHouse"), nullptr);
	
	return EBTNodeResult::Succeeded;
}