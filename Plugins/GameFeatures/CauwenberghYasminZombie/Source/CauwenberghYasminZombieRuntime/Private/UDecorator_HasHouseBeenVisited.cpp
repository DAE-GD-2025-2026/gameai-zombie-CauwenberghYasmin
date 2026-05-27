// Fill out your copyright notice in the Description page of Project Settings.


#include "UDecorator_HasHouseBeenVisited.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "SurvivorAccessor.h"
#include "Village/House/House.h"

UUDecorator_HasHouseBeenVisited::UUDecorator_HasHouseBeenVisited()
{
	NodeName = TEXT("HasHouseBeenVisited");
}


bool UUDecorator_HasHouseBeenVisited::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (!blackboard) return EBTNodeResult::Failed;
	
	ASurvivorAccessor* survivorAcc = static_cast<ASurvivorAccessor*>(survivor);
	
	AHouse* currHouse {Cast<AHouse>(blackboard->GetValueAsObject("TargetHouse"))};
	
	for (auto house :survivorAcc->visitedHouses )
	{
		if (house == currHouse)
		{
			return false;
		}
	}
	return true;
}