// Fill out your copyright notice in the Description page of Project Settings.


#include "UDecorator_IsTrue.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/ValueOrBBKey.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"


UUDecorator_IsTrue::UUDecorator_IsTrue()
{
	NodeName = TEXT("IsBoolTrue");
	BoolKeySelector.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UUDecorator_IsTrue, BoolKeySelector)); //CHECK IF WORKS!!!
}


bool UUDecorator_IsTrue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	bool boolean = blackBoard->GetValueAsBool(BoolKeySelector.SelectedKeyName);
	
	if (boolean == true)
	{
		return true;
	}
	
	//else
	return false;
}