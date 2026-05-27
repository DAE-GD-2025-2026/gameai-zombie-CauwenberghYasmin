// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_Wander.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "CircleTypes.h"

UUTask_Wander::UUTask_Wander()
{
	NodeName = "Wander around";
}

EBTNodeResult::Type UUTask_Wander ::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* TaskMemory)
{
	AAIController* AIController = OwnerComponent.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(AIController->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	float angleChange = FMath::FRandRange(-m_MaxAngleChange, m_MaxAngleChange);
	m_WanderAngle += angleChange;
	m_WanderAngle = FMath::UnwindDegrees(m_WanderAngle); //-> bless this function
	float radianAngle = FMath::DegreesToRadians(m_WanderAngle);
	
    FVector2D posCirlce = FVector2D{survivor->GetActorLocation().X + (survivor->GetActorForwardVector().X * m_OffsetDistance), survivor->GetActorLocation().Y + (survivor->GetActorForwardVector().Y * m_OffsetDistance)};
	UE::Geometry::FCircle2d circle (posCirlce, 100.f);
	
	FVector targetPos {posCirlce.X + (circle.Radius * cos(radianAngle)), posCirlce.Y + (circle.Radius * sin(radianAngle)), 0 };
    FVector direction= (targetPos - survivor->GetActorLocation()).GetSafeNormal();
	
	FVector goalLocation = survivor->GetActorLocation() + (direction * 800.0f);
	TArray<FVector> pathPoints = survivor->CalculatePath(goalLocation);
	
	if (pathPoints.Num() != 0)
	{
		survivor->StartRunning();
		AIController->MoveToLocation(pathPoints[1], 50.0f, false, true, true, true, 0, true);
		return EBTNodeResult::Succeeded; 
	}
	
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
FString::Printf(TEXT("Wandering failed")));
	return EBTNodeResult::Failed;
	
}


// float m_OffsetDistance = 120.f;
// float m_Radius = 4.f;
// float m_MaxAngleChange = 15; // = 45 degrees
// float m_WanderAngle = 180.f;


// SteeringOutput Wander::CalculateSteering(float DeltaT, ASteeringAgent& Agent)	
// {
// 	SteeringOutput steering{};
//
// 	
// 	
// 	UE::Geometry::FCircle2d WanderCIrlce (posCirlce, 100.f);
// 	
// 	//DrawLineTraces()
// 	DrawDebugCircle(Agent.GetWorld(), FVector{posCirlce.X, posCirlce.Y, 5}, 100.f , 32, FColor::Blue, false, -1, 0, 0, FVector(0,1,0), FVector(1,0,0), true);
// 	
// 	DrawDebugPoint(Agent.GetWorld(), FVector{targetPos.X, targetPos.Y, 1}, 7, FColor::Green);
// 	
// 	drawDebugLines(steering, Agent);
// 	
// 	return steering;
// }