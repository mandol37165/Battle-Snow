// Fill out your copyright notice in the Description page of Project Settings.


#include "StopPoint.h"

// Sets default values
AStopPoint::AStopPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStopPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStopPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

