// Fill out your copyright notice in the Description page of Project Settings.


#include "MagneticField.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AMagneticField::AMagneticField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	this->SetRootComponent(sphereComp);

	magneticFieldComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("magneticFieldComp"));
	magneticFieldComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (tempMesh.Succeeded()) {
		magneticFieldComp->SetStaticMesh(tempMesh.Object);

		ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/ddoza/Material/MagneticField.MagneticField' "));
		if (tempMat.Succeeded()) {
			magneticFieldComp->SetMaterial(0, tempMat.Object);
			magneticFieldComp->SetRelativeLocationAndRotation(FVector(-290, 0, 0), FRotator(0, 0, 0));
			magneticFieldComp->SetRelativeScale3D(FVector(100, 100, 100));
			magneticFieldComp->SetupAttachment(sphereComp);
		}
	}

	magneticFieldComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName("MageneticField");

}

// Called when the game starts or when spawned
void AMagneticField::BeginPlay()
{
	Super::BeginPlay();

	state = EMFState::Ready;

}

// Called every frame
void AMagneticField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (state)
	{
	case EMFState::Ready:
		readyState();
		break;
	case EMFState::activateMF:
		currentTime += GetWorld()->GetDeltaSeconds();
		if (currentTime >= 5) {
			activateMFState();
			currentTime = 0;
		}
		break;
	}
}

void AMagneticField::readyState()
{
	currentTime += GetWorld()->GetDeltaSeconds();
	//플레이 30초 뒤부터 자기장 줄어들도록
	if (currentTime > 30) {
		UE_LOG(LogTemp, Warning, TEXT("10 sec"));
		state = EMFState::activateMF;
	}
}

void AMagneticField::activateMFState()
{
	makeMFSmall();
}

void AMagneticField::makeMFSmall()
{
	UE_LOG(LogTemp, Warning, TEXT("make it small"));
		FVector targetScale;
		FVector actorScale = this->GetActorScale3D();
		//5초마다
		targetScale.X = actorScale.X * 0.90;
		targetScale.Y = actorScale.Y * 0.90;
		targetScale.Z = 1.0;

		SetActorScale3D(FMath::Lerp<FVector>(actorScale, targetScale, 0.1));
		
	
}

