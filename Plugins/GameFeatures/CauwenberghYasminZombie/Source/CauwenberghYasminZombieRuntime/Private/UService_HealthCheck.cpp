// Fill out your copyright notice in the Description page of Project Settings.


#include "UService_HealthCheck.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h" 
#include "Common/HealthComponent.h"




UUService_HealthCheck::UUService_HealthCheck()
{
	NodeName = TEXT("Check Health Service");
	bNotifyTick = true; 
	
}

void UUService_HealthCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	
	UHealthComponent * healthComp = survivor->GetComponentByClass<UHealthComponent>();
	
	if (firstTick)
	{
		blackBoard->SetValueAsInt(FName("CurrentHealth"), healthComp->GetMaxHealth());
		firstTick = false;
	}

	
	if (survivor)
	{
		int CurrentHealth = healthComp->GetHealth();
		
		if (CurrentHealth < blackBoard->GetValueAsInt(FName("CurrentHealth"))) //damaged
		{
			blackBoard->SetValueAsInt(FName("CurrentHealth"), CurrentHealth);
			blackBoard->SetValueAsBool(FName("TookDamage"), true);
		}
		else if (CurrentHealth > blackBoard->GetValueAsInt(FName("CurrentHealth"))) //healed (medkit)
		{
			blackBoard->SetValueAsInt(FName("CurrentHealth"), CurrentHealth);
		}
		
	}
}