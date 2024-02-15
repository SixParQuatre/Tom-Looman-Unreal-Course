// Fill out your copyright notice in the Description page of Project Settings.


#include "TTInteractionComponent.h"
#include "TTGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UTTInteractionComponent::UTTInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTTInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTTInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UTTInteractionComponent::PrimaryInteract()
{
	AActor* actorOwner = GetOwner(); 
	APawn* ownerPawn = Cast<APawn>(actorOwner);
	if (ownerPawn == nullptr)
		return;
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector Start, End;
	FRotator Dir;
	actorOwner->GetActorEyesViewPoint(Start, Dir);
	
	End = Start + Dir.Vector() * InteractionDistance;
	TArray<FHitResult> results;
	FCollisionShape sweepShape;
	sweepShape.SetSphere(SweepRadius);

	FColor debugColor = FColor::Red;
	int debugSphereSegment = 32;
	float debugDuration = 2.f;

	bool foundHit = GetWorld()->SweepMultiByObjectType(results, Start, End,FQuat::Identity, ObjectQueryParams, sweepShape);
	if (foundHit)
	{ 
		debugColor = FColor::Orange;
		for (FHitResult result : results)
		{

			AActor* hitActor = result.GetActor();
			if (hitActor != nullptr && hitActor->Implements<UTTGameplayInterface>())
			{
				ITTGameplayInterface::Execute_Interact(hitActor, ownerPawn);
				debugColor = FColor::Green; 
				DrawDebugSphere(GetWorld(), result.ImpactPoint, sweepShape.GetSphereRadius(), debugSphereSegment, debugColor, false, debugDuration);
				break;
			}
			else
				DrawDebugSphere(GetWorld(), result.ImpactPoint, sweepShape.GetSphereRadius(), debugSphereSegment, debugColor, false, debugDuration);
		}
	}
	else
	{
		DrawDebugSphere(GetWorld(), Start, sweepShape.GetSphereRadius(), debugSphereSegment, debugColor, false, debugDuration);
	}
	DrawDebugLine(GetWorld(), Start, End, debugColor, false, 1.f, 0, debugDuration);
}

