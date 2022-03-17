// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Bullet.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/Engine.h"
#include "CharGhost.h"

// Sets default values
ACharGhost::ACharGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharGhostMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharGhostMesh")); //skeletal
	//SetRootComponent(UCapsuleComponent); 

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;


	//SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);

	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(CharGhostMesh);


	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;

	/*UCharacterMovementComponent* const MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->bUseControllerDesiredRotation = false;
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;*/

}

// Called when the game starts or when spawned
void ACharGhost::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ACharGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACharGhost::MoveForward);
	//PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACharGhost::MoveRight);

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ACharGhost::Shoot);
	//PlayerInputComponent->BindAction("MouseLeft", EInputEvent::IE_Pressed, this, &ACharGhost::Shoot);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ACharGhost::Reload);
	//PlayerInputComponent->BindAction("MouseRight", EInputEvent::IE_Pressed, this, &ACharGhost::Reload);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACharGhost::MoveRight);
}


void ACharGhost::MoveForward(float value)
{
	//CurrentVelocity.X = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves CharGhost forward or backwards. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)

	FVector Direction = FRotationMatrix(Controller->GetActorRotation());
	//FVector Direction = Set //GetActorRotation();
	AddMovementInput(Direction, value);
	AddMovementInput



}

void ACharGhost::MoveRight(float value)
{
	//CurrentVelocity.Y = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves CharGhost left or right. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)

	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//AddMovementInput(Direction, value);

	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0)); 
	}

}

void ACharGhost::Shoot()
{
	if (Ammo > 0) {
		Ammo--;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ammo : !"), FString::FromInt(Ammo)); 
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::Printf(TEXT("Ammo :  %d "), Ammo));


		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = GetActorLocation();
			//150cm ahead of actor the bullet will be spawn 
			World->SpawnActor<AActor>(ActorToSpawn, Location + FVector(250.f, 0.f, 0.f), GetActorRotation());
			UGameplayStatics::PlaySound2D(World, ShootingSound, 1.f, 1.f, 0.f, 0);

		}
		if (Ammo == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("No ammo Reload %d "), Ammo));

		}
	}



	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
}

void ACharGhost::Reload()
{
	if (Ammo < 10)
	{
		Ammo = 10;
		UWorld* NewWorld = GetWorld();
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("Reloaded")));
	}
}

