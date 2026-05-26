// Fill out your copyright notice in the Description page of Project Settings.


#include "UService_HealthCheck.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h" // Your pawn class
#include "Common/HealthComponent.h"
#include "SurvivorAccessor.h"



UUService_HealthCheck::UUService_HealthCheck()
{
	NodeName = TEXT("Check Health Service");
	bNotifyTick = true; // IMPORTANT: This tells the service to run TickNode
	
	//set blackboard variable to max health
}

void UUService_HealthCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	

	if (survivor)
	{
		ASurvivorAccessor* survivorAcc = static_cast<ASurvivorAccessor*>(survivor);
		int CurrentHealth = survivorAcc->GetHealthComp()->GetHealth();
		
		//get variable
		//if smaller
		//set bool
		Blackboard->SetValueAsFloat(FName("CurrentHealth"), CurrentHealth);
		
		//else if bigger
		//only reset the value, dont set the bool!
	}
}