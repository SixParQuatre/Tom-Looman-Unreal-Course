// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTreasureChest.h"
#include "TTGameplayInterface.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATTTreasureChest::ATTTreasureChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isOpen = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	RootComponent = Body;

	Lid = CreateDefaultSubobject<UStaticMeshComponent>("Lid");
	Lid->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATTTreasureChest::BeginPlay()
{
	Super::BeginPlay();
	
}

 bool ATTTreasureChest::Interact_Implementation(APawn* instigator)
{
	Lid->SetRelativeRotation(FRotator(fOpenPitch, 0, 0));
	isOpen = true;
	return true;
}

// Called every frame
void ATTTreasureChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

