// Fill out your copyright notice in the Description page of Project Settings.


#include "TTExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "TTMagicProjectile.h"
#include "TTAttributeComponent.h"

// Sets default values
ATTExplosiveBarrel::ATTExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMeshComp->SetSimulatePhysics(true);
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("Radial Force");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->SetAutoActivate(false);

	DamageSphere = CreateDefaultSubobject<USphereComponent>("Damage Sphere");
	DamageSphere->SetupAttachment(RootComponent);
}

void ATTExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ATTExplosiveBarrel::OnComponentHit);
}
// Called when the game starts or when spawned
void ATTExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ATTExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ATTMagicProjectile* HitActor = Cast<ATTMagicProjectile>(OtherActor))
	{
		if (HitActor->DoesDamageOnHit())
		{
			Explode();
			UE_LOG(LogTemp, Log, TEXT("Explosive Barrel Explode"));
			UE_LOG(LogTemp, Warning, TEXT("Actor %s at gametime %f"), *GetNameSafe(OtherActor), GetWorld()->GetTimeSeconds());
			FString msg = FString::Printf(TEXT("Hit at location %s"), *Hit.ImpactPoint.ToString());
			DrawDebugString(GetWorld(), Hit.ImpactPoint, msg, nullptr, FColor::Green, 2.f, true);

			TArray<AActor*> outOverlappingActors;
			DamageSphere->GetOverlappingActors(outOverlappingActors);
			for (AActor* overlapingActor : outOverlappingActors)
			{
				
				UTTAttributeComponent* cpt = overlapingActor->GetComponentByClass<UTTAttributeComponent>();
				if (cpt == nullptr)
					continue;

				cpt->ApplyHealthChange(DamageOnExplode);
			}

		}
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

