// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LOOMANUNREALCOURSE_API ATTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATTCharacter();

	void MoveForward(float val);
	void MoveRight(float val);
	void PrimaryAttack();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
 	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
