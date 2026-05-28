
#include "UTask_PickUpItem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "Common/InventoryComponent.h"
#include "Items/BaseItem.h"
#include "Items/ItemType.h"

UUTask_PickUpItem::UUTask_PickUpItem()
{
	NodeName = "Pick up item";
}

EBTNodeResult::Type UUTask_PickUpItem ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	AAIController* AIController = OwnerComponent.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UBlackboardComponent* blackboard = OwnerComponent.GetBlackboardComponent();
	if (!blackboard) return EBTNodeResult::Failed;
	
	ABaseItem* item = Cast<ABaseItem>(blackboard->GetValueAsObject("TargetItem"));
	
	int currSlot = blackboard->GetValueAsInt("currentSlotInventory");
	
	
	if ( /*item->GetItemType() != EItemType::Garbage || */  currSlot <= 4 )
	{
		if (currSlot <= 0) currSlot = 0;
		
		survivor->GetComponentByClass<UInventoryComponent>()->GrabItem(currSlot, item);
		blackboard->SetValueAsInt("currentSlotInventory", (currSlot+1));	
		
		
		//make this switch case!
		if (item->GetItemType()== EItemType::Pistol || item->GetItemType() == EItemType::Shotgun)
		{
			blackboard->SetValueAsInt("HasWeapon", true);
		}
		else if (item->GetItemType()== EItemType::Food)
		{
			blackboard->SetValueAsInt("HasFood", true);
		}
		else if (item->GetItemType()== EItemType::Medkit)
		{
			blackboard->SetValueAsInt("HasMedKit", true);
		}
		
		return EBTNodeResult::Succeeded;
	}

	
	//garbage, dont pick up but still succeed!
	return EBTNodeResult::Succeeded;
}