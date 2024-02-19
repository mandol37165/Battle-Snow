// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagneticField.generated.h"

UENUM()
enum class EMFState : uint8
{
	Ready,
	activateMF,
};

UCLASS()
class BATTLESNOW_API AMagneticField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagneticField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=FSM)
	EMFState state ;

	void readyState();
	void activateMFState();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* magneticFieldComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* sphereComp;
	
	float currentTime = 0;

	void makeMFSmall();
};
