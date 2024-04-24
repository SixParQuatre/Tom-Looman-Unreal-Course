// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTMagicProjectile.h"
#include "TTGameplayInterface.h"


#include "TTTreasureChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class LOOMANUNREALCOURSE_API ATTTreasureChest : public AActor, public ITTGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATTTreasureChest(); 
	
	

	UPROPERTY(EditAnywhere)
	double fOpenPitch = 110;

	bool Interact_Implementation(APawn* instigator);
	void CanInteract_Implementation(APawn* instigator, bool& result) { result = isOpen; }
private:
	bool isOpen;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Lid;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
