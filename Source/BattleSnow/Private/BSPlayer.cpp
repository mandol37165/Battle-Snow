// Fill out your copyright notice in the Description page of Project Settings.


#include "BSPlayer.h"
#include "Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "ARBulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"

// Sets default values
ABSPlayer::ABSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, 70, 90));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Models/BSPlayer/Ch01_nonPBR.Ch01_nonPBR'"));
	// 성공했다면
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		//GetMesh()->SetRelativeScale3D(FVector(4.0f));
	}

	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	firePos = CreateDefaultSubobject<UArrowComponent>(TEXT("firePos"));
	firePos->SetupAttachment(GetMesh());
	firePos->SetRelativeLocationAndRotation(FVector(-20, 10, 140), FRotator(0, 90, 0));
}

// Called when the game starts or when spawned
void ABSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

// Called to bind functionality to input
void ABSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ABSPlayer::OnAxisVertical);

	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &ABSPlayer::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &ABSPlayer::OnAxisTurnYaw);

	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &ABSPlayer::OnAxisLookupPitch);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABSPlayer::OnActionJump);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ABSPlayer::OnActionFire);

}

void ABSPlayer::Move()
{
	FTransform trans = GetActorTransform();
	AddMovementInput(trans.TransformVector(direction));
}

void ABSPlayer::OnAxisVertical(float value)
{
	direction.X = value * 10;
}

void ABSPlayer::OnAxisHorizontal(float value)
{
	direction.Y = value * 10;
}

void ABSPlayer::OnAxisTurnYaw(float value)
{
	AddControllerYawInput(value);
}

void ABSPlayer::OnAxisLookupPitch(float value)
{
	AddControllerPitchInput(value);
}

void ABSPlayer::OnActionJump()
{
	Jump();
}

void ABSPlayer::OnActionFire()
{
	FTransform t = firePos->GetRelativeTransform();
	GetWorld()->SpawnActor<AARBulletActor>(bulletFactory, t);
}


