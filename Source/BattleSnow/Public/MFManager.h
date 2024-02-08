// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MFManager.generated.h"

UCLASS()
class BATTLESNOW_API AMFManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMFManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	FVector MFLocation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMagneticField> magneticFieldFactory;
	
};