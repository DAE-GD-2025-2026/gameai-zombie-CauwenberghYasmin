// Fill out your copyright notice in the Description page of Project Settings.


#include "UDecorator_NeedsToEatFood.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/ValueOrBBKey.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "Survivor/SurvivorPawn.h"
#include "AIController.h"
#include "Common/StaminaComponent.h"

UUDecorator_NeedsToEatFood::UUDecorator_NeedsToEatFood()
{
	NodeName = TEXT("Need To Use Resources");
	BoolKeySelector.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UUDecorator_NeedsToTakeMedKit, BoolKeySelector));
}

bool UUDecorator_NeedsToEatFood::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	bool boolean = blackBoard->GetValueAsBool(BoolKeySelector.SelectedKeyName);
	
	
	if (!boolean)
	{
		return false;
	}
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	
	UStaminaComponent* StamicaComp = survivor->GetComponentByClass<UStaminaComponent>();
	if (StamicaComp->GetCurrentStamina() < (StamicaComp->GetMaxStamina() * 0.4f) )
	{
		return true;
	}
	
	return false;
}










// bool UUDecorator_IsTrue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
// {
// 	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
// 	bool boolean = blackBoard->GetValueAsBool(BoolKeySelector.SelectedKeyName);
// 	
// 	if (boolean == true)
// 	{
// 		return true;
// 	}
// 	
// 	//else
// 	return false;
// }