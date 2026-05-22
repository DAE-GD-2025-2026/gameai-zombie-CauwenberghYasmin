// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"
#include "Zombies/BaseZombie.h"

//https://forums.unrealengine.com/t/quick-ai-perception-jumpstart-c/27452
UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	//PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));	//need to get!
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));

	if (SightConfig)
	{
		SightConfig->SightRadius = 2000.f;
		SightConfig->LoseSightRadius = 2500.f;
		SightConfig->PeripheralVisionAngleDegrees = 60.f; // 120-degree cone total
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		// Assign the configuration to the perception component
		auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>();
		PerceptionComp->ConfigureSense(*SightConfig);
		//PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());	//make feeling dominant, (being attacked > seeing smth? (depends on what they saw no?))
	}
	
	if (DamageConfig)
	{
		//DamageConfig->Set
		
		auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>();
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->SetDominantSense(DamageConfig->GetSenseImplementation());
	}
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
	}
}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)			//use ForgetAll () if it's inside a purge zone!!
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	//check what was sensed/what sense it used!!
	//-> then update the black board (?), some other model will do the decision making!
	if (Stimulus.WasSuccessfullySensed())
	{
		if ( ABaseZombie * SensedZombie = Cast<ABaseZombie>(Actor))
		{
			// We saw a zombie! Write it to the Blackboard.
			// "TargetEnemy" must perfectly match the Key Name in your Blackboard asset.
			//Blackboard->SetValueAsObject(FName("TargetEnemy"), SensedZombie);
		}
		//else if (AMedkit* SensedMedkit = Cast<AMedkit>(Actor))
		{
			//Blackboard->SetValueAsObject(FName("TargetFirstAid"), SensedMedkit);
		}
	}
	
}
