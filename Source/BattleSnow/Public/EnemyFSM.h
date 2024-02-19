// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"
//#include "Enemy.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Ready,
    GetTarget,
    Patrol,
    Hide,
    AttackReady,
    ShootReady,
    Damage,
    Escape,
    Die,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FSM)
    EEnemyState state;

    void ReadyState();
    void GetTargetState();
    void PatrolState(FVector targetDir);
    void HideState();
    void AttackReadyState();
    void ShootState();
    void DamageState();
    void EscapeState();
    void DieState();


    void startShooting();
    void moveToLR();
    UPROPERTY(EditAnywhere, Category = FSM)
    float idleDelayTime = 2;
    float currentTime = 0;
    float shootingTime = 0;
    //플레이어 타겟
    UPROPERTY(EditAnywhere, Category = FSM)
    AActor* targetP;

    UPROPERTY(EditAnywhere)
    class AEnemy* me;

    //슈팅 반경 안에 들어오면 슈팅모드로 전환
    UPROPERTY(EditAnywhere, Category = FSM)
    float shootingRange = 7000;
    UPROPERTY(EditAnywhere, Category = FSM)
    float shootingRangeShort = 500.0f;
    UPROPERTY(EditAnywhere, Category = FSM)
    float shootingRangeMid = 1500.0f;
    UPROPERTY(EditAnywhere, Category = FSM)
    float shootingRangeLong = 2500.0f;

    //attackRange 범위 안에 들어오면 공격준비모드로 전환
    UPROPERTY(EditAnywhere, Category = FSM)
    float attackReadyRange = 12000.0f;

    UPROPERTY(EditAnywhere, Category = FSM)
    float escapeRange = 8000.0f;

    //공격 대기 시간
    UPROPERTY(EditAnywhere, Category = FSM)
    float attackDelayTime = 2.0f;

    FVector dir;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy)
    int32 enemyMaxHP = 100;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy)
    int32 enemyCurrentHP = 0;

    UPROPERTY(EditAnywhere)
    class AEnemy* enemy;

    int32 weaponInfo;

    UPROPERTY(EditAnywhere)
    class USoundBase* fireSFX;

    UPROPERTY(EditAnywhere)
    float SearchRadius = 1000.0f;

    UPROPERTY(EditAnywhere)
    float MoveInterval = 5.0f;

    FTimerHandle MoveTimerHandle;

    void MoveToRandomLocation();

    void SetTargetAndAttack(ACharacter* TargetCharacter);
};