// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_UseMedKit.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "Common/InventoryComponent.h"
#include "Items/BaseItem.h"
#include "Items/ItemType.h"

UUTask_UseMedKit::UUTask_UseMedKit()
{
	NodeName = "Use medkit";
}

EBTNodeResult::Type UUTask_UseMedKit ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	AAIController* AIController = OwnerComponent.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UInventoryComponent* InventoryComponent = survivor->GetComponentByClass<UInventoryComponent>();
	UBlackboardComponent* blackBoard = OwnerComponent.GetBlackboardComponent();
	
	const TArray<ABaseItem*>& CurrentItems = InventoryComponent->GetInventory();
	int SlotToUse = -1;


	for (int i = 0; i < CurrentItems.Num(); ++i)
	{
		if (CurrentItems[i] != nullptr && CurrentItems[i]->GetItemType() == EItemType::Medkit)
		{
			SlotToUse = i;
			break; 
		}
	}
	
	if (SlotToUse != -1)
	{
		InventoryComponent->UseItem(SlotToUse);
		return EBTNodeResult::Succeeded;
	}
	
	blackBoard->ClearValue("TargetMedKit");
	return EBTNodeResult::Failed;
}