// Fill out your copyright notice in the Description page of Project Settings.


#include "TTAttributeComponent.h"

// Sets default values for this component's properties
UTTAttributeComponent::UTTAttributeComponent()
{
	fHealth = fMaxHealth;
}



bool UTTAttributeComponent::ApplyHealthChange(float delta, AActor* Instigator)
{
	if (FMath::IsNearlyZero(delta))
		return false;

	if (fHealth <= 0 && delta < 0)
		return false;

	if (fHealth >= fMaxHealth && delta > 0)
		return false;

	float oldHealth = fHealth;
	fHealth += delta;
	fHealth = FMath::Clamp(fHealth, 0, fMaxHealth);
	if (oldHealth != fHealth)
	{
		OnHealthChanged.Broadcast(Instigator, this, oldHealth, fHealth);
		return true;
	}
	return false;
}

