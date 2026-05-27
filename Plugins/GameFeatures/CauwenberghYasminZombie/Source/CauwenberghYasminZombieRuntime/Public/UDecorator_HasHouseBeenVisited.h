// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UDecorator_HasHouseBeenVisited.generated.h"

/**
 * 
 */
UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUDecorator_HasHouseBeenVisited : public UBTDecorator
{
	GENERATED_BODY()
	UUDecorator_HasHouseBeenVisited();
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
