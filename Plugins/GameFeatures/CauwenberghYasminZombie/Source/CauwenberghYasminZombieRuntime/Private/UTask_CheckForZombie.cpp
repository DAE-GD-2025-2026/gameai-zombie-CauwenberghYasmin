// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_CheckForZombie.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombies/BaseZombie.h"
#include "Survivor/SurvivorPawn.h"

UUTask_CheckForZombie::UUTask_CheckForZombie()
{
	NodeName = "Scan Around";
	
	bNotifyTick = true; //task gets to tick every frame :D
	RotationSpeed = 780.0f;
	DegreesSpun = 0.0f;
}

EBTNodeResult::Type UUTask_CheckForZombie ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	//START TASK
	DegreesSpun = 0.0f;
	return EBTNodeResult::InProgress;
	
	
	// Survivor->AddActorWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
}

void UUTask_CheckForZombie::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//this is the continueing task (so after start)
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	ASurvivorPawn* Survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!Survivor)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	AIController->StopMovement(); //from the switch from wander
	
	float DegreesToRotateThisFrame = RotationSpeed * DeltaSeconds;
	Survivor->AddActorWorldRotation(FRotator(0.0f, DegreesToRotateThisFrame, 0.0f));
	DegreesSpun += DegreesToRotateThisFrame;
	
	if (DegreesSpun >= 360.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); //after succeed the task will stop so no infinte spin :>
	}
}