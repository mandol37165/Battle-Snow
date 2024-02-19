// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RenderCharacter.generated.h"

UCLASS()
class BATTLESNOW_API ARenderCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARenderCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* renderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ak47RSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ak47LSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ak47HandPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* benelliM4RSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* benelliM4LSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* benelliM4HandPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* barretRSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* barretLSPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* barretHandPos;
};
