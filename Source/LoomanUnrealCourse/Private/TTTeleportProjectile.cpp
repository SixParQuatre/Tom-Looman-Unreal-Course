// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTeleportProjectile.h"
#include "Components/SphereComponent.h"

void ATTTeleportProjectile::OnComponentHitOvr(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ignoreFurtherHits)
		return;


	ignoreFurtherHits = true;

	GetWorldTimerManager().SetTimer(TeleportTimer, this, &ATTTeleportProjectile::TeleportTimer_Elapsed, TeleportDelay);

	teleportPoint = Hit.ImpactPoint;

	SpawnAt(FXAtInstigator, GetInstigator()->GetActorLocation(), GetInstigator()->GetActorRotation());
	SpawnAt(FXAtArrival, teleportPoint, Hit.ImpactNormal.Rotation());

}

void ATTTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &ATTTeleportProjectile::OnComponentHit);
	this->DamagesOnImpact = false;

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

}

void ATTTeleportProjectile::SpawnAt(UClass* toSpawn, FVector spawnPos, FRotator rot)
{
	FTransform SpawnTM = FTransform(rot, spawnPos);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = GetInstigator();
	GetWorld()->SpawnActor<AActor>(toSpawn, SpawnTM, SpawnParams);
}

void ATTTeleportProjectile::TeleportTimer_Elapsed()
{
	GetInstigator()->TeleportTo(teleportPoint, this->GetActorRotation(), false, false);
	Destroy();
	
}