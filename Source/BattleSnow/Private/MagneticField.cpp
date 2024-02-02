// Fill out your copyright notice in the Description page of Project Settings.


#include "MagneticField.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AMagneticField::AMagneticField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	this->SetRootComponent(sphereComp);

	magneticFieldComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("magneticFieldComp"));
	magneticFieldComp->SetupAttachment(RootComponent);

	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName("MageneticField");

	magneticFieldComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AMagneticField::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagneticField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

