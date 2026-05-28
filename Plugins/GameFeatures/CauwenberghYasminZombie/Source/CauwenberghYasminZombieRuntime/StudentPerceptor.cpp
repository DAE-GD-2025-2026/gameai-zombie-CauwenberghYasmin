// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

//items to check for:
#include "Zombies/BaseZombie.h"
#include "Items/Food.h"
#include "Items/Medkit.h"
#include "Items/Pistol.h"
#include "Items/Shotgun.h"
#include "PurgeZones/PurgeZone.h"
#include "Village/House/House.h"


//https://forums.unrealengine.com/t/quick-ai-perception-jumpstart-c/27452
UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	// DONT SET UP, ALREADY DONE IN SURIVOR PAWN!!
	
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>()) //from surviror pawn
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
	}
}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	
	AAIController* AIController = Cast<AAIController>(OwnerPawn->GetController());
	if (!AIController) return;
	
	UBlackboardComponent* blackBoard = AIController->GetBlackboardComponent();
	if (!blackBoard) return;
	
	
	
	FAISenseID DamageSenseID = UAISense::GetSenseID<UAISense_Damage>();
	if (Stimulus.WasSuccessfullySensed() && Stimulus.Type == DamageSenseID)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Red, 
FString::Printf(TEXT("Sensing Damage")));
	}
	
	
	
	//check what was sensed/what sense it used!!
	//-> then update the black board (?), some other model will do the decision making!
	if (Stimulus.WasSuccessfullySensed())												//WILL DO ALL THE SENSING HERE 
	{
		if (APurgeZone * sensedPurgeZone = Cast<APurgeZone>(Actor))
		{
			blackBoard->SetValueAsObject(FName("TargetPurgeZone"),sensedPurgeZone);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw purge!")));
		}
		
		if ( ABaseZombie * SensedZombie = Cast<ABaseZombie>(Actor))
		{
			//SensedZombie->zombietype
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw zombie!")));
			blackBoard->SetValueAsObject(FName("TargetZombie"), SensedZombie); //if more than one zombie, pick shotgun (more bullets)
		}
	
		
		//making items seperate so the ai doesn't go and pick up trash
		if (AFood* SensedFood = Cast<AFood>(Actor))
		{
			blackBoard->SetValueAsObject(FName("TargetFood"), SensedFood);
			blackBoard->SetValueAsObject(FName("TargetItem"), SensedFood);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw food!")));
		}
		
		if (AMedkit* SensedMedkit = Cast<AMedkit>(Actor))
		{
			blackBoard->SetValueAsObject(FName("TargetMedkit"), SensedMedkit);
			blackBoard->SetValueAsObject(FName("TargetItem"), SensedMedkit);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Medkit!")));
		}
		
		if (APistol* SensedPistol = Cast<APistol>(Actor))//pistol
		{
			blackBoard->SetValueAsObject(FName("TargetPistol"), SensedPistol);
			blackBoard->SetValueAsObject(FName("TargetItem"), SensedPistol);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw pistol!")));
		}
		
		if (AShotgun* SensedShotGun = Cast<AShotgun>(Actor))//shotgun
		{
			blackBoard->SetValueAsObject(FName("TargetShotgun"), SensedShotGun);
			blackBoard->SetValueAsObject(FName("TargetItem"), SensedShotGun);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw shotgun!")));
		}
		
		if (AHouse* SensedHouse = Cast<AHouse>(Actor)) //house
		{
			//if house not in list visitedHouses!! TODO: this!
			blackBoard->SetValueAsObject(FName("TargetHouse"), SensedHouse);
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw house!")));
		}
	}
	
	//we'll have to check if health is going down
	//make service checking if health changing
	//change boolean in the blackboard?
    
	// FAISenseID DamageSenseID = UAISense::GetSenseID<UAISense_Damage>();
	// if (Stimulus.Type == DamageSenseID)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("attackFromBehind"));
	// 	if (blackBoard)
	// 	{
	// 		blackBoard->SetValueAsObject(FName("TargetZombie"), Actor);
	// 	}
	// }
}
