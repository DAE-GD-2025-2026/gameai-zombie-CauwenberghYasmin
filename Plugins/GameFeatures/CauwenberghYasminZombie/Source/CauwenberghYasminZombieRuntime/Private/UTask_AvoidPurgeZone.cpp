// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_AvoidPurgeZone.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PurgeZones/PurgeZone.h"
#include "Survivor/SurvivorPawn.h"


UUTask_AvoidPurgeZone::UUTask_AvoidPurgeZone()
{
	NodeName = "Run Away From Zombie";
}

EBTNodeResult::Type UUTask_AvoidPurgeZone ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	//get all var needed
	AAIController* AIController = OwnerComponent.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* Survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!Survivor) return EBTNodeResult::Failed;
	
	UBlackboardComponent* Blackboard = OwnerComponent.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;
	//---------------------------------------------------
	
	APurgeZone* PurgeZone = Cast<APurgeZone>(Blackboard->GetValueAsObject(FName("TargetPurgeZone"))); //get from blackboard
	if (!PurgeZone) return EBTNodeResult::Failed; //security, but there should always be a zombie target (goes thorugh decorator)
	


	FVector playerLocation = Survivor->GetActorLocation();
	FVector zombieLocaion = PurgeZone->GetActorLocation();
	FVector direction = (playerLocation - zombieLocaion).GetSafeNormal();
    
	//target to run towards
	FVector EscapeTargetLocation = playerLocation + (direction * 300.0f);
	
	TArray<FVector> PathPoints = Survivor->CalculatePath(EscapeTargetLocation); //BLESSS
	
	if (PathPoints.Num() != 0)
	{
		Survivor->StartRunning();
		AIController->MoveToLocation(PathPoints[1], 50.0f, false, true, true, true, 0, true);
		return EBTNodeResult::Succeeded; 
		
	}
	
	return EBTNodeResult::Failed;
}