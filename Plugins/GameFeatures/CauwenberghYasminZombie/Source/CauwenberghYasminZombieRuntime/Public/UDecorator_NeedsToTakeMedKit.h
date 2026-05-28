// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UDecorator_NeedsToTakeMedKit.generated.h"

/**
 * 
 */
UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUDecorator_NeedsToTakeMedKit : public UBTDecorator
{
	GENERATED_BODY()
	UUDecorator_NeedsToTakeMedKit();
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	
	UPROPERTY(EditAnywhere, Category = "Blackboard") 
	FBlackboardKeySelector BoolKeySelector; //has it
	
};
