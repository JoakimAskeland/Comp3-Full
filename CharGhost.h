// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//#include "Components/CapsuleComponent.h"
#include "CharGhost.generated.h"

UCLASS()
class COMP3_API ACharGhost : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		USkeletalMeshComponent* CharGhostMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Character Movement")
		float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		int Ammo = 10;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		USoundBase* ShootingSound = nullptr;




private:
	void MoveForward(float value); 
	void MoveRight(float value);

	void Shoot();
	void Reload();


	//FVector CurrentVelocity;

};
