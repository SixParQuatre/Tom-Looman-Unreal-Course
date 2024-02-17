// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UTTInteractionComponent;
class UAnimMontage;
class UTTAttributeComponent;

UCLASS()
class LOOMANUNREALCOURSE_API ATTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATTCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UTTInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTTAttributeComponent* AttributeComponent;

	
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;


	UPROPERTY(EditAnywhere, Category = "Attack")
	float TargetDistance = 10000.0f;
	FVector currentTargettingPoint;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackDelay = 0.2f;
	
	UPROPERTY(EditAnywhere, Category = "Primary Attack")
	TSubclassOf<AActor> ProjectileClass;

	FTimerHandle PrimaryAttackTimer;

	UPROPERTY(EditAnywhere, Category = "Secondary Attack")
	TSubclassOf<AActor> Blackhole;

	UPROPERTY(EditAnywhere, Category = "Special Ability")
	TSubclassOf<AActor> SpecialAbilityProjectile;


	UPROPERTY(EditAnywhere, Category = "Damage Received")
	float DamageflashDuration = 1.f;

	UPROPERTY(EditAnywhere, Category = "Damage Received")
	FColor DamageFlashColor = FColor::Red;

	FTimerHandle SecondaryAttackTimer;


	void MoveForward(float val);
	void MoveRight(float val);
	void PrimaryAttack();
	void PrimaryInteract();
	void SecondaryAttack();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	void SpecialAbility();

	FTimerHandle SpecialAbilityTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: 
	void UpdateTargettingPoint();
	void SpawnFromEndToCrosshair(UClass* toSpawn);

	void ProjectileActionDelayed(UAnimMontage* actionAnim, FTimerHandle& actionTimer, float actionDelay, UClass* projectileToSpawn);

	UFUNCTION()
	void OnHealthChanged(AActor* _instigator, UTTAttributeComponent* source, float oldHealth, float newHealth);

	virtual void  PostInitializeComponents();

};
