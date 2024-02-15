	// Fill out your copyright notice in the Description page of Project Settings.


#include "TTCharacter.h"

#include "GameFramework/SpringArmComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "TTInteractionComponent.h"
#include "TTAttributeComponent.h" 

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

	AttributeComponent = CreateDefaultSubobject<UTTAttributeComponent>("Attribute Component");


	InteractionComp = CreateDefaultSubobject<UTTInteractionComponent>("InteractionComponent");

	this->bUseControllerRotationYaw = false;	

	this->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ATTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ATTCharacter::OnHealthChanged);
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


void ATTCharacter::UpdateTargettingPoint()
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;


	FVector TraceStart;
	FRotator CameraDir;
	GetActorEyesViewPoint(TraceStart, CameraDir);
	TraceStart = CameraComp->GetComponentLocation();

	// We set up a line trace from our current location to a point 10000cm ahead of us
	currentTargettingPoint = TraceStart + CameraDir.Vector() * TargetDistance;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	float minDist = TargetDistance + 1.f;
	ECollisionChannel channels[2] = { ECC_WorldDynamic , ECC_WorldStatic };
	for (ECollisionChannel channel : channels)
	{
		// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
		// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, currentTargettingPoint, channel, QueryParams);

		// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.

		//UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

		// If the trace hit something, bBlockingHit will be true,
		// and its fields will be filled with detailed info about what was hit
		if (Hit.bBlockingHit && Hit.Distance < minDist)
		{
			minDist = Hit.Distance;
			currentTargettingPoint = Hit.ImpactPoint;
		}
	}
	//DrawDebugLine(GetWorld(), TraceStart, cachedPrimaryAttackTargetPoint, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

}	

void ATTCharacter::PrimaryInteract() { this->InteractionComp->PrimaryInteract(); }

void ATTCharacter::PrimaryAttack() { ProjectileActionDelayed(AttackAnim, PrimaryAttackTimer, AttackDelay , this->ProjectileClass);}

void ATTCharacter::SecondaryAttack() { ProjectileActionDelayed(AttackAnim, SecondaryAttackTimer, AttackDelay, this->Blackhole); }

void ATTCharacter::SpecialAbility() { ProjectileActionDelayed(AttackAnim, SpecialAbilityTimer, AttackDelay, this->SpecialAbilityProjectile); }


void ATTCharacter::ProjectileActionDelayed(UAnimMontage* actionAnim, FTimerHandle& actionTimer, float actionDelay, UClass* projectileToSpawn)
{
	FTimerDelegate del;
	del.BindLambda([this, projectileToSpawn]() { SpawnFromEndToCrosshair(projectileToSpawn); });
	PlayAnimMontage(actionAnim);
	GetWorldTimerManager().SetTimer(actionTimer, del, actionDelay, false);
	UpdateTargettingPoint();
}

void ATTCharacter::OnHealthChanged(AActor* _instigator, UTTAttributeComponent* source, float oldHealth, float newHealth)
{
	if (oldHealth > 0  && newHealth <= 0)
		DisableInput(Cast<APlayerController>(GetController()));
}

void ATTCharacter::SpawnFromEndToCrosshair(UClass* toSpawn)
{
	FVector spawnPos = GetMesh()->GetSocketLocation("Muzzle_01");

	FVector dir = (currentTargettingPoint - spawnPos);
	dir.Normalize();
	FTransform SpawnTM = FTransform(dir.Rotation(), spawnPos);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>(toSpawn, SpawnTM, SpawnParams);
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
	
	PlayerInputComponent->BindAction("SecondaryAttack", EInputEvent::IE_Pressed, this, &ATTCharacter::SecondaryAttack);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("SpecialAbility", EInputEvent::IE_Pressed, this, &ATTCharacter::SpecialAbility);

}

