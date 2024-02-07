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

	//UFUNCTION()
	//void OnPlayerCompEndOverlap( UPrimitiveComponent* OverlappedComponent ,
	//	AActor* OtherActor ,
	//	UPrimitiveComponent* OtherComp ,
	//	int32 OtherBodyIndex ,
	//	bool bFromSweep ,
	//	const FHitResult& SweepResult );

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* capsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ak47AttachPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ak47ShoulderPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ak47LSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* benelliM4HandPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* benelliM4RSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* benelliM4LSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* barretHandPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* barretRSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* barretLSPos;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerMaxHP = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerCurrentHP = playerMaxHP;

	void PlayerTakeDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEquipRifle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEquipRifleOnHand = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCrouch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsProne = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFire = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxAmmoAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentAmmoAmount;

	void OnActionAiming();

	void OnActionZoomIn();

	void OnActionZoomOut();

	void Zoom();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float targetFOV = 90;
};
