// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayer.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

// Sets default values
ALobbyPlayer::ALobbyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, 30, 90));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Models/BSPlayer/Remy.Remy'"));
	// 성공했다면
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.5f));
	}

	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called when the game starts or when spawned
void ALobbyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALobbyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

// Called to bind functionality to input
void ALobbyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ALobbyPlayer::OnAxisVertical);

	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &ALobbyPlayer::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &ALobbyPlayer::OnAxisTurnYaw);

	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &ALobbyPlayer::OnAxisLookupPitch);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ALobbyPlayer::OnActionJump);

	PlayerInputComponent->BindAction(TEXT("ActionCrouch"), IE_Pressed, this, &ALobbyPlayer::OnActionCrouch);

}

void ALobbyPlayer::Move()
{
	FTransform trans = GetActorTransform();
	AddMovementInput(trans.TransformVector(direction.GetSafeNormal2D()));
}

void ALobbyPlayer::OnAxisVertical(float value)
{
	direction.X = value * 5;
}

void ALobbyPlayer::OnAxisHorizontal(float value)
{
	direction.Y = value * 5;
}

void ALobbyPlayer::OnAxisTurnYaw(float value)
{
	AddControllerYawInput(value);
}

void ALobbyPlayer::OnAxisLookupPitch(float value)
{
	AddControllerPitchInput(value);
}

void ALobbyPlayer::OnActionJump()
{
	bIsJumping = true;
	Jump();
}

void ALobbyPlayer::OnActionCrouch()
{
	if (false == bIsCrouch)
	{
		bIsCrouch = true;
		GetCharacterMovement()->Crouch();
	}
	else
	{
		bIsCrouch = false;
		GetCharacterMovement()->UnCrouch();
	}
}

