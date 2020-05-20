// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	OurCharacter = CreateDefaultSubobject<USkeletalMeshComponent>("OurCharacterMesh");

	//Find and load the mesh from disk to memory and it in CharacterMesh Varible.
	auto CharacterMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	//Assign that mesh to our Character.
	if (CharacterMesh.Object != nullptr)
	{
		OurCharacter->SetSkeletalMesh(CharacterMesh.Object);
	}

	//To Set the Mesh properly into Capsule Collision Mesh.
	OurCharacter->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));

	//To form a Hierarchy.
	Root = RootComponent;
	OurCharacter->SetupAttachment(Root);
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

}

