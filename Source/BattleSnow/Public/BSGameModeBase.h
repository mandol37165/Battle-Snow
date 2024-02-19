// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESNOW_API ABSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 countOfSurvivors = 5;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 killCount = 0;
};
