// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UTask_Wander.generated.h"

/**
 * 
 */
UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUTask_Wander : public UBTTaskNode
{
	GENERATED_BODY()
	UUTask_Wander();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
	
	float m_OffsetDistance = 120.f;
	float m_Radius = 4.f;
	float m_MaxAngleChange = 15; // = 45 degrees
	float m_WanderAngle = 180.f;
};
