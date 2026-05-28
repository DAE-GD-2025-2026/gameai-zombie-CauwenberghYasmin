// Fill out your copyright notice in the Description page of Project Settings.


#include "UTask_Wander.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "CircleTypes.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

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
    m_WanderAngle = FMath::UnwindDegrees(m_WanderAngle); 
    float radianAngle = FMath::DegreesToRadians(m_WanderAngle);
	
    FVector actorLoc = survivor->GetActorLocation();
    FVector forwardVec = survivor->GetActorForwardVector();
    
    FVector2D posCircle = FVector2D{actorLoc.X + (forwardVec.X * m_OffsetDistance), actorLoc.Y + (forwardVec.Y * m_OffsetDistance)};
    float radius = 100.f;
    
    FVector targetPos {posCircle.X + (radius * cos(radianAngle)), posCircle.Y + (radius * sin(radianAngle)), actorLoc.Z};
    FVector direction = (targetPos - actorLoc).GetSafeNormal();
    FVector rawGoalLocation = actorLoc + (direction * 800.0f);
	
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()); //make sure not in wall
    if (!NavSys) return EBTNodeResult::Failed;

    FNavLocation ProjectedLocation;
    bool bFoundValidSpot = NavSys->ProjectPointToNavigation(rawGoalLocation, ProjectedLocation, FVector(200.f, 200.f, 200.f));
	survivor->StopRunning();

    if (bFoundValidSpot)
    {
        EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(ProjectedLocation.Location, 50.0f, false, true, true, true, 0, true);
        
        if (MoveResult != EPathFollowingRequestResult::Type::Failed)
        {
            return EBTNodeResult::Succeeded;
        }
    }
	
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