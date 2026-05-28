// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UTask_EatFood.generated.h"

/**
 * 
 */
UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUTask_EatFood : public UBTTaskNode
{
	GENERATED_BODY()
	UUTask_EatFood();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;

};
