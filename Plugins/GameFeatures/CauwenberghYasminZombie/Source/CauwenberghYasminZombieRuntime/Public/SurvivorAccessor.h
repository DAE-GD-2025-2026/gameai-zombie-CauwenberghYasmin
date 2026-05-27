// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Survivor/SurvivorPawn.h"
#include "Village/House/House.h"

//NO CREATED INSTANCE!
class ASurvivorAccessor : public ASurvivorPawn
{
public:
	//since the components are protected in the survivorpawn class, I deciced to make an accessor class
	//this way I can check currenthealth/invontory, etc in c++ instead of only the blueprints
	UInventoryComponent* GetInventory() const { return InventoryComponent; }
	UHealthComponent* GetHealthComp() const { return HealthComponent; }
	UStaminaComponent* GetStaminaComp() const { return StaminaComponent; }
	UFloatingPawnMovement* GetMovementComp() const { return FloatingPawnMovement; }
	UAIPerceptionComponent* GetPerceptionComp() const { return PerceptionComp; }
	
	TArray<AHouse*> visitedHouses{};
};