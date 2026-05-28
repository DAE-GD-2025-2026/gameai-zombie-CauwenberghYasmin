// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UTask_PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUTask_PickUpItem : public UBTTaskNode
{
	GENERATED_BODY()
	UUTask_PickUpItem();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
};
