// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLESNOW_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=FSM)
	EEnemyState state = EEnemyState::Idle;
	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();
		
	UPROPERTY(EditAnywhere,Category=FSM)
	float idleDelayTime =2;
	float currentTime = 0;

	UPROPERTY(EditAnywhere,Category=FSM)
	AActor* target;

	UPROPERTY(EditAnywhere)
	class AEnemy* me;

	//attackRange 범위 안에 들어오면 공격모드로 전환
	UPROPERTY(EditAnywhere,Category=FSM)
	float attackRange=300.0f;

	//공격 대기 시간
	UPROPERTY(EditAnywhere,Category=FSM)
	float attackDelayTime=7.0f;


};
