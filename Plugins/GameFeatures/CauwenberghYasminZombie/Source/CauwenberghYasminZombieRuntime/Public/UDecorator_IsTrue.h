// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UDecorator_IsTrue.generated.h"


//why is this no a decorator IN UNREAL?????


UCLASS()
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUDecorator_IsTrue : public UBTDecorator
{
	GENERATED_BODY()
	UUDecorator_IsTrue();
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	
	UPROPERTY(EditAnywhere, Category = "Blackboard") //ley's you add keys in the bt, so reusable with different ones!
	FBlackboardKeySelector BoolKeySelector;
};
