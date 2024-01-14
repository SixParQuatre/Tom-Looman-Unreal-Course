	// Fill out your copyright notice in the Description page of Project Settings.


#include "TTCharacter.h"

#include "GameFramework/SpringArmComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATTCharacter::ATTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Sprint Camera Component");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComponent);

	this->bUseControllerRotationYaw = false;	

	this->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ATTCharacter::MoveForward(float val)
{
	FRotator controlRot = this->GetControlRotation();
	controlRot.Pitch = .0f;
	controlRot.Roll = .0f;
	FVector vec = controlRot.Vector();
	AddMovementInput(vec, val);
}

void ATTCharacter::MoveRight(float val)
{
	FRotator controlRot = this->GetControlRotation();
	controlRot.Pitch = .0f;
	controlRot.Roll = .0f;
	FVector vec = UKismetMathLibrary::GetRightVector(this->GetControlRotation());

	AddMovementInput(vec, val);
}

// Called when the game starts or when spawned
void ATTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATTCharacter::PrimaryAttack()
{
	FVector spawnPos = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTM = FTransform(GetControlRotation(), spawnPos);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}


// Called to bind functionality to input
void ATTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATTCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATTCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &ATTCharacter::PrimaryAttack);

}

