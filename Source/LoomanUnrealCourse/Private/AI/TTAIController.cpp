// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TTAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ATTAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	APawn* player = UGameplayStatics::GetPlayerPawn(this, 0);
	if (player)
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", player);
	}
}
