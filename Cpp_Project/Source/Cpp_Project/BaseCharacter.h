// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CPP_PROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* Root = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		USkeletalMeshComponent* OurCharacter = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		USpringArmComponent* CameraArm = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UCameraComponent* OurCamera = nullptr;

public:
	UPROPERTY()
		float ArmLength { 300.f };

	UPROPERTY()
		float CameraLag{ 4.f };

public:
	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void CameraYaw(float Value);

	UFUNCTION()
		void CameraPitch(float Value);
};