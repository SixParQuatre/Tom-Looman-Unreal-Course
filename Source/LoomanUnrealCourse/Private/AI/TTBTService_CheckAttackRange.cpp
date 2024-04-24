// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TTBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UTTBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (ensure(blackboard))
	{
		AActor* targetActor = Cast<AActor>(blackboard->GetValueAsObject("TargetActor"));
		if (targetActor)
		{
			AAIController* ctrler = OwnerComp.GetAIOwner();
			if (ensure(ctrler))
			{
				APawn* aiPawn = ctrler->GetPawn();
				if (aiPawn)
				{
					float dist = FVector::Distance(aiPawn->GetActorLocation(), targetActor->GetActorLocation());
					bool inRange = dist < Range;
					bool hasLOS = false;
					if (inRange)
						hasLOS = ctrler->LineOfSightTo(targetActor);
					blackboard->SetValueAsBool(InRangeVar.SelectedKeyName, inRange && hasLOS);
					return;
				}

			}
		}
		blackboard->SetValueAsBool(InRangeVar.SelectedKeyName, false);

	}
}