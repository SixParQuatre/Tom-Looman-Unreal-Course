// Fill out your copyright notice in the Description page of Project Settings.


#include "TTMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
//#include "Components/Widget.h"


#include "TTAttributeComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ATTMagicProjectile::ATTMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("UProjectileMovementComponent");
	RootComponent = SphereComp;	

	SphereComp->SetCollisionProfileName("TTProjectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATTMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &ATTMagicProjectile::OnComponentHit);
		
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;


	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");

}

void ATTMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}


// Called when the game starts or when spawned
void ATTMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}


void ATTMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!DamagesOnImpact)
		return;

	if (OtherActor == nullptr)
		return;

	UTTAttributeComponent* attComp = Cast<UTTAttributeComponent>(OtherActor->GetComponentByClass<UTTAttributeComponent>());
	if (attComp == nullptr)
		return;
	if (attComp->ApplyHealthChange(-Damage))// && DamageWidget != nullptr)
	{
		if (APawn* instigator = GetInstigator())
		{
			//CreateWidget(instigator->GetController(), DamageWidget);

		}
	}
	OnFinalHit(GetWorld(), SweepResult.Location, GetActorRotation());
}

void ATTMagicProjectile::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OnComponentHitOvr(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
void ATTMagicProjectile::OnComponentHitOvr(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OnFinalHit(GetWorld(), Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

void ATTMagicProjectile::OnFinalHit(UWorld* world, FVector location, FRotator orientation)
{
	UGameplayStatics::PlaySoundAtLocation(world, ImpactSound, location, orientation);
	UGameplayStatics::SpawnEmitterAtLocation(world, ImpactFX, location, orientation);
	Destroy();
}
