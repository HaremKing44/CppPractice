// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	OurCharacter = CreateDefaultSubobject<USkeletalMeshComponent>("OurCharacterMesh");
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	OurCamera = CreateDefaultSubobject<UCameraComponent>("OurCamera");

	//Find and load the mesh from disk to memory and save it in CharacterMesh Varible.
	auto CharacterMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	//Assign that mesh to our Character.
	if (CharacterMesh.Object != nullptr)
	{
		OurCharacter->SetSkeletalMesh(CharacterMesh.Object);
	}

	//To Set the Mesh properly into Capsule Collision Mesh.
	OurCharacter->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));

	//Setup for Basic Camera.
	CameraArm->TargetArmLength = ArmLength;
	CameraArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 50.f), FRotator(-15.f, 0.f, 0.f));
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = CameraLag;
	CameraArm->bUsePawnControlRotation = true;

	//To form a Hierarchy.
	Root = RootComponent;
	OurCharacter->SetupAttachment(Root);
	CameraArm->SetupAttachment(Root);
	OurCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerYaw", this, &ABaseCharacter::CameraYaw);
	PlayerInputComponent->BindAxis("PlayerPitch", this, &ABaseCharacter::CameraPitch);

	PlayerInputComponent->BindAxis("GamepadCameraTurnRate", this, &ABaseCharacter::GPadCameraTurn);
	PlayerInputComponent->BindAxis("GamepadCameraLookUpRate", this, &ABaseCharacter::GPadCameraLookUp);
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller) && (Value != 0))
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller) && (Value != 0))
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABaseCharacter::CameraYaw(float Value)
{
	if ((Controller) && (Value != 0))
	{
		AddControllerYawInput(Value);
	}
}

void ABaseCharacter::CameraPitch(float Value)
{
	if ((Controller) && (Value != 0))
	{
		AddControllerPitchInput(Value);
	}
}

void ABaseCharacter::GPadCameraTurn(float Value)
{
	if ((Controller) && (Value != 0))
	{
		float Delta = GetWorld()->GetDeltaSeconds();
		float TurnValue = Value * BaseTurnRate * Delta;
		AddControllerYawInput(TurnValue);
	}
}

void ABaseCharacter::GPadCameraLookUp(float Value)
{
	if ((Controller) && (Value != 0))
	{
		float Delta = GetWorld()->GetDeltaSeconds();
		float TurnValue = Value * BaseLookUpRate * Delta;
		AddControllerPitchInput(TurnValue);
	}
}