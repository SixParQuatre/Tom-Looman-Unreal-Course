// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTMagicProjectile.h"
#include "TTTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class LOOMANUNREALCOURSE_API ATTTeleportProjectile : public ATTMagicProjectile
{
	GENERATED_BODY()

	
	void PostInitializeComponents();

	FTimerHandle TeleportTimer;
	void TeleportTimer_Elapsed();

public:
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<AActor> FXAtInstigator;
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<AActor> FXAtArrival;

protected:
	UPROPERTY(EditAnywhere)
	float TeleportDelay = 0.2f;
	
	FVector teleportPoint;

	void SpawnAt(UClass* toSpawn, FVector spawnPos, FRotator rot);

	virtual void OnComponentHitOvr(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	bool ignoreFurtherHits = false;

		
};
