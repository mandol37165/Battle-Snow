// Fill out your copyright notice in the Description page of Project Settings.


#include "WinnerPlayer.h"

// Sets default values
AWinnerPlayer::AWinnerPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Models/BSPlayer/Remy.Remy'"));
	// 성공했다면
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.5f));
	}

	rChickenPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RchickenPos"));
	rChickenPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> temprChicken(TEXT("/Script/Engine.StaticMesh'/Game/Megascans/3D_Assets/Grilled_Turkey_Leg_wd5lcfcaa/S_Grilled_Turkey_Leg_wd5lcfcaa_lod3_Var1.S_Grilled_Turkey_Leg_wd5lcfcaa_lod3_Var1'"));

	if (temprChicken.Succeeded())
	{
		rChickenPos->SetStaticMesh(temprChicken.Object);
		rChickenPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightChicken"));
		rChickenPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// rChickenPos->SetVisibility(false);
	}

	lChickenPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LchickenPos"));
	lChickenPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> templChicken(TEXT("/Script/Engine.StaticMesh'/Game/Megascans/3D_Assets/Roasted_Chicken_Leg_wd5ffbnaa/S_Roasted_Chicken_Leg_wd5ffbnaa_lod3_Var1.S_Roasted_Chicken_Leg_wd5ffbnaa_lod3_Var1'"));

	if (templChicken.Succeeded())
	{
		lChickenPos->SetStaticMesh(templChicken.Object);
		lChickenPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftChicken"));
		lChickenPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// lChickenPos->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void AWinnerPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWinnerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWinnerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

