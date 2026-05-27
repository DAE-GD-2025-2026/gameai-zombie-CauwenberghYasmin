// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UTask_CheckForZombie.generated.h"

/**
 * 
 */
UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUTask_CheckForZombie : public UBTTaskNode
{
	GENERATED_BODY()
	UUTask_CheckForZombie();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float DegreesSpun;
	float RotationSpeed;
};
