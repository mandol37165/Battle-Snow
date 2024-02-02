// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BSPlayer.generated.h"

UCLASS()
class BATTLESNOW_API ABSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* capsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* cameraComp;

	FVector direction;

	void Move();

	void OnAxisVertical(float value);
	void OnAxisHorizontal(float value);

	void OnAxisTurnYaw(float value);		// Yaw
	void OnAxisLookupPitch(float value);	// Pitch

	void OnActionJump();

	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePos;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AARBulletActor> bulletFactory;

	void OnActionFire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJumping = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOnWidget;
};
