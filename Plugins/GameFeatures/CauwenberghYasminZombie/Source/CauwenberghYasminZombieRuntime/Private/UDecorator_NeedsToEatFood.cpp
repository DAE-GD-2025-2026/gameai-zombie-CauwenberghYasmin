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
	BoolKeySelector.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UUDecorator_NeedsToEatFood, BoolKeySelector));
}

bool UUDecorator_NeedsToEatFood::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	bool boolean = blackBoard->GetValueAsBool(BoolKeySelector.SelectedKeyName);
	
	
	if (!boolean)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("has food is false")));
		return false;
	}
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	
	UStaminaComponent* StamicaComp = survivor->GetComponentByClass<UStaminaComponent>();
	if (StamicaComp->GetCurrentStamina() < 4) //(StamicaComp->GetMaxStamina() * 0.4f) )
	{
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("needs food")));
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("stamine high enough")));
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