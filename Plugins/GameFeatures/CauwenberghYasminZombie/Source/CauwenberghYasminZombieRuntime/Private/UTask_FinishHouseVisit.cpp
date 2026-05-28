// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_FinishHouseVisit.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "Village/House/House.h"
#include "UDecorator_HasHouseBeenVisited.h"
#include "UKey_HouseArray.h"

UUTask_FinishHouseVisit::UUTask_FinishHouseVisit()
{
	NodeName = "Mark house as visited";
}

EBTNodeResult::Type UUTask_FinishHouseVisit ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	AAIController* AIController = OwnerComponent.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UBlackboardComponent* blackboard = OwnerComponent.GetBlackboardComponent();
	if (!blackboard) return EBTNodeResult::Failed;
	
	
	UObject* temp = blackboard->GetValueAsObject("VisitedHousesList");
	UUKey_HouseArray* HouseListWrapper = Cast<UUKey_HouseArray>(temp);
    HouseListWrapper->VisitedHouses.Add( Cast<AHouse>(blackboard->GetValueAsObject(FName("TargetHouse"))));
	blackboard->SetValueAsObject(FName("TargetHouse"), nullptr);
	
	return EBTNodeResult::Succeeded;
}

