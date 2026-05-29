// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_ShootWeapon.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "Common/InventoryComponent.h"
#include "Items/BaseItem.h"
#include "Items/Pistol.h"
#include "Items/Shotgun.h"

UUTask_ShootWeapon::UUTask_ShootWeapon()
{
    NodeName = "Shoot Weapon";
}

EBTNodeResult::Type UUTask_ShootWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
    AAIController* AIController = OwnerComponent.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
    if (!survivor) return EBTNodeResult::Failed;
    
    UInventoryComponent* InventoryComponent = survivor->GetComponentByClass<UInventoryComponent>();
    if (!InventoryComponent) return EBTNodeResult::Failed;
    
    const TArray<ABaseItem*>& CurrentItems = InventoryComponent->GetInventory();
    int WeaponSlot = -1;
    ABaseItem* WeaponItem = nullptr;
   
    for (int i = 0; i < CurrentItems.Num(); ++i)
    {
       if (CurrentItems[i] != nullptr && 
          (CurrentItems[i]->GetItemType() == EItemType::Pistol || CurrentItems[i]->GetItemType() == EItemType::Shotgun))
       {
          WeaponSlot = i;
          WeaponItem = CurrentItems[i];
          break; 
       }
    }
   
    if (WeaponSlot == -1)
    {
       OwnerComponent.GetBlackboardComponent()->SetValueAsBool("HasWeapon", false);
       return EBTNodeResult::Failed;
    }

    bool bHasAmmo = false;
   
   if (WeaponItem->GetItemType() == EItemType::Shotgun)
   {
      AShotgun* Gun = Cast<AShotgun>(WeaponItem);
       bHasAmmo = Gun->GetValue() > 0;
   }
   else if (WeaponItem->GetItemType() == EItemType::Pistol)
   {
      APistol* Gun = Cast<APistol>(WeaponItem);
       bHasAmmo = Gun->GetValue() > 0;
   }
   
    
    if (bHasAmmo)
    {
       InventoryComponent->UseItem(WeaponSlot);
       return EBTNodeResult::Succeeded;
    }
    else
    {
       InventoryComponent->RemoveItem(WeaponSlot); 
       OwnerComponent.GetBlackboardComponent()->SetValueAsBool("HasWeapon", false);
       return EBTNodeResult::Succeeded; 
    }
}
