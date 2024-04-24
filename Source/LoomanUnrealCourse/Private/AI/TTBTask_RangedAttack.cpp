// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TTBTask_RangedAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UTTBTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (!ensure(MyController))
		return EBTNodeResult::Failed;
	
	ACharacter* myPawn = Cast<ACharacter>(MyController->GetPawn());
	if (myPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector spawnPos = myPawn->GetMesh()->GetSocketLocation("Muzzle_01");
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if(target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector dir = target->GetActorLocation() - spawnPos;
	FRotator ori = dir.Rotation();
			
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
	AActor* obj = GetWorld()->SpawnActor<AActor>(ProjectileClass, spawnPos, ori, SpawnParams);

	return obj != nullptr ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;

}
