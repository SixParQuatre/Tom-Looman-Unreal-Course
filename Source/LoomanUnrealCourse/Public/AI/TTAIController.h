// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TTAIController.generated.h"

/**
 * 
 */
UCLASS()
class LOOMANUNREALCOURSE_API ATTAIController : public AAIController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
};
