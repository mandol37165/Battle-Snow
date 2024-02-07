// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderCharacter.h"

// Sets default values
ARenderCharacter::ARenderCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

