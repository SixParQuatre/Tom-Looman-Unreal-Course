// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundBase;
class UParticleSystem;
//class UWidget;

UCLASS()
class LOOMANUNREALCOURSE_API ATTMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATTMagicProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;


	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;	

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool DamagesOnImpact = true;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactFX;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	//UPROPERTY(EditAnywhere)
	//UWidget* DamageWidget;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnComponentHitOvr(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	bool DoesDamageOnHit() { return DamagesOnImpact; }

	virtual void PostInitializeComponents() override;

private:
	void OnFinalHit(UWorld* world, FVector location, FRotator orientation);


};
