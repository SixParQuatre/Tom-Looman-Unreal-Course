// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UTTInteractionComponent;
class UAnimMontage;

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

	UPROPERTY(VisibleAnywhere)
	UTTInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere, Category = "Primary Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Primary Attack")
	UAnimMontage* AttackAnim;

 	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	void PrimaryInteract();


	UPROPERTY(EditAnywhere, Category = "Primary Attack")
	float PrimaryProjectileDelay = 0.5f;


	FTimerHandle PrimaryAttackTimer;
	FRotator cachedPrimaryAttackDir;

	void PrimaryAttack_Delayed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
