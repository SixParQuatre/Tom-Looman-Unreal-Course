// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/CoreDelegates.h"
#include "Components/ActorComponent.h"
#include "TTAttributeComponent.generated.h"	

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, Instigator, class UTTAttributeComponent*, OwningComp, float, OldHealth, float, NewHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOMANUNREALCOURSE_API UTTAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float fHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float fMaxHealth = 100.f;
public:	

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float delta, AActor* Instigator = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const { return fHealth > 0; };

		
};
