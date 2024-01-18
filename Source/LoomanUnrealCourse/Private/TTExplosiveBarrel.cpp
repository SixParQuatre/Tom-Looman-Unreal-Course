// Fill out your copyright notice in the Description page of Project Settings.


#include "TTExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

#include "TTMagicProjectile.h"

// Sets default values
ATTExplosiveBarrel::ATTExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMeshComp->SetSimulatePhysics(true);
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("Radial Force");
	RadialForceComp->SetupAttachment(StaticMeshComp);
}

// Called when the game starts or when spawned
void ATTExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ATTExplosiveBarrel::OnComponentHit);
}

void ATTExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ATTMagicProjectile* HitActor = Cast<ATTMagicProjectile>(OtherActor))
	{
		OtherActor->Destroy();
		Explode();
	}

}
void ATTExplosiveBarrel::Explode()
{
	RadialForceComp->FireImpulse();
	this->Destroy();
}

// Called every frame
void ATTExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

