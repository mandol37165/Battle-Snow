// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"

// Sets default values
ARenderCharacter::ARenderCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	renderMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("renderMesh"));
	renderMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Models/BSPlayer/Remy.Remy'"));
	// 성공했다면
	if (tempMesh.Succeeded())
	{
		renderMesh->SetSkeletalMesh(tempMesh.Object);
		//renderMesh->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		renderMesh->SetWorldRotation(FRotator(0, -90, 0));
		renderMesh->SetRelativeScale3D(FVector(0.5f));
	}

	ak47RSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AK47RSPos"));
	ak47RSPos->SetupAttachment(renderMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempAKShoulderMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/AR/AK47/AK47.AK47'"));

	if (tempAKShoulderMesh.Succeeded())
	{
		ak47RSPos->SetStaticMesh(tempAKShoulderMesh.Object);
		ak47RSPos->AttachToComponent(renderMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("AK47ShoulderSocket"));
		ak47RSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ak47RSPos->SetVisibility(false);
	}

	ak47LSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AK47LSPos"));
	ak47LSPos->SetupAttachment(renderMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempAK47LSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/AR/AK47/AK47.AK47'"));

	if (tempAK47LSMesh.Succeeded())
	{
		ak47LSPos->SetStaticMesh(tempAK47LSMesh.Object);
		ak47LSPos->AttachToComponent(renderMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("AK47LSSocket"));
		ak47LSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ak47LSPos->SetVisibility(false);
	}

	benelliM4RSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BenelliM4RSPos"));
	benelliM4RSPos->SetupAttachment(renderMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBenelliRSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SG/Benelli_M4/Benelli_M4.Benelli_M4'"));

	if (tempBenelliRSMesh.Succeeded())
	{
		benelliM4RSPos->SetStaticMesh(tempBenelliRSMesh.Object);
		benelliM4RSPos->AttachToComponent(renderMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BenelliM4RSSocket"));
		benelliM4RSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		benelliM4RSPos->SetVisibility(false);
	}

	benelliM4LSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BenelliM4LSPos"));
	benelliM4LSPos->SetupAttachment(renderMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBenelliLSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SG/Benelli_M4/Benelli_M4.Benelli_M4'"));

	if (tempBenelliLSMesh.Succeeded())
	{
		benelliM4LSPos->SetStaticMesh(tempBenelliLSMesh.Object);
		benelliM4LSPos->AttachToComponent(renderMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BenelliM4LSSocket"));
		benelliM4LSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		benelliM4LSPos->SetVisibility(false);
	}

	barretRSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarretRSPos"));
	barretRSPos->SetupAttachment(renderMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBarretRSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SR/Barret/Barret_Fix.Barret_Fix'"));

	if (tempBarretRSMesh.Succeeded())
	{
		barretRSPos->SetStaticMesh(tempBarretRSMesh.Object);
		barretRSPos->AttachToComponent(renderMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BarretRSSocket"));
		barretRSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		barretRSPos->SetVisibility(false);
	}

	barretLSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarretLSPos"));
	barretLSPos->SetupAttachment(renderMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBarretLSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SR/Barret/Barret_Fix.Barret_Fix'"));

	if (tempBarretLSMesh.Succeeded())
	{
		barretLSPos->SetStaticMesh(tempBarretLSMesh.Object);
		barretLSPos->AttachToComponent(renderMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BarretLSSocket"));
		barretLSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		barretLSPos->SetVisibility(false);
	}

}

// Called when the game starts or when spawned
void ARenderCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARenderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

