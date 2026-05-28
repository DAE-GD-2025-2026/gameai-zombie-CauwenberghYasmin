// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UDecorator_NeedsToEatFood.generated.h"

/**
 * 
 */
UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUDecorator_NeedsToEatFood : public UBTDecorator
{
	GENERATED_BODY()
	UUDecorator_NeedsToEatFood();
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	
	UPROPERTY(EditAnywhere, Category = "Blackboard") 
	FBlackboardKeySelector BoolKeySelector; 
};
