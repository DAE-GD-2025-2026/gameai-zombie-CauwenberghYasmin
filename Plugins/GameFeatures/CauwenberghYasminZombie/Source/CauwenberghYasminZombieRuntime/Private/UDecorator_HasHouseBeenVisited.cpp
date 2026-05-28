// Fill out your copyright notice in the Description page of Project Settings.


#include "UDecorator_HasHouseBeenVisited.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "Village/House/House.h"
#include "UKey_HouseArray.h"
#include "BehaviorTree/BlackboardComponent.h"

UUDecorator_HasHouseBeenVisited::UUDecorator_HasHouseBeenVisited()
{
	NodeName = TEXT("HasHouseBeenVisited");
}


bool UUDecorator_HasHouseBeenVisited::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return false;

	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!survivor) return false;
	
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (!blackboard) return false;
	
	
	if (blackboard->GetValueAsObject("VisitedHousesList") == nullptr) {
		UUKey_HouseArray* MyHouseList = NewObject<UUKey_HouseArray>(blackboard);
		blackboard->SetValueAsObject("VisitedHousesList", MyHouseList);
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Red, 
			FString::Printf(TEXT("created array")));
	}
	
	
	AHouse* currHouse {Cast<AHouse>(blackboard->GetValueAsObject("TargetHouse"))};
	
	if (currHouse != nullptr)
	{
		//UObject* temp = blackboard->GetValueAsObject("VisitedHousesList");
		UUKey_HouseArray* HouseListWrapper = Cast<UUKey_HouseArray>(blackboard->GetValueAsObject("VisitedHousesList"));
		
		if (!HouseListWrapper)
		{
			HouseListWrapper = NewObject<UUKey_HouseArray>(blackboard);
			blackboard->SetValueAsObject("VisitedHousesList", HouseListWrapper);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Red, 
            FString::Printf(TEXT("Can't find house array, made one")));
			
		}
		
		for (auto house : HouseListWrapper->VisitedHouses )
		{
			if (house == currHouse)
			{
				return false;
			}
		}
		
		return true;
	}
	
	return false;
}

