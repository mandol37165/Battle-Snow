// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class BATTLESNOW_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	class UEnemyFSM* fsm;

public:
	int32 weaponNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* weaponMeshComp0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* weaponMeshComp1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* weaponMeshComp2;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePos;

public:
	
	void OnFire() const;

	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AARBulletActor> bulletFactory;

	
};
