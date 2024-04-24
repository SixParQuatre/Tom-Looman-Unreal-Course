// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TTBTService_CheckAttackRange.generated.h"

class UBehaviorTreeComponent;
class UBlackboardKeySelector;
/**
 * 
 */
UCLASS()
class LOOMANUNREALCOURSE_API UTTBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UPROPERTY(EditAnywhere)
	float Range = 2000.f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector InRangeVar;
	
};
