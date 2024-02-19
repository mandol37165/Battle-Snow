// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "BSPlayer.h"
#include "Enemy.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MFManager.h"
#include "EngineUtils.h"
#include "ARBulletActor.h"
#include "TimerManager.h"
#include "BSGameModeBase.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
    Super::BeginPlay();

    enemyCurrentHP = enemyMaxHP;
    // 무기 정보 가져오기
    me = Cast<AEnemy>(GetOwner());

    /*if (me) {
       weaponInfo = me->weaponNum;
       UE_LOG(LogTemp, Warning, TEXT("%s"),weaponInfo );
    }*/
    GetRandomChasePoint(SearchRadius, chasePoint);
    //초기 모드 getTarget

    state = EEnemyState::Ready;


}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    switch (state)
    {
    case EEnemyState::Ready:
        ReadyState();
        break;
    case EEnemyState::GetTarget:
        GetTargetState();
        break;
    case EEnemyState::Patrol:
        PatrolState(dir);
        break;
    case EEnemyState::Hide:
        HideState();
        break;
    case EEnemyState::AttackReady:
        AttackReadyState();
        break;
    case EEnemyState::ShootReady:
        ShootState();
        break;
    case EEnemyState::Damage:
        DamageState();
        break;
    case EEnemyState::Escape:
        EscapeState();
        break;
    case EEnemyState::Die:
        DieState();
        break;


    }
}

void UEnemyFSM::ReadyState()
{
    me->SetActorHiddenInGame(true);
    currentTime += GetWorld()->GetDeltaSeconds();
    if (currentTime > 10) {
        me->SetActorHiddenInGame(false);
        state = EEnemyState::GetTarget;
    }
}

void UEnemyFSM::GetTargetState()
{
    int randValue;
    randValue = rand() % 2;
    targetP = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (randValue == 0) {
        //플레이어로 타겟 설정
        dir = targetP->GetActorLocation() - me->GetActorLocation();
    }

    else if (randValue == 1) {

        AMFManager* MFManager = Cast<AMFManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMFManager::StaticClass()));
        //for (TActorIterator<AMFManager> it(GetWorld()); it; ++it){MFManager = *it;
        //자기장 중심을 목표점으로 설정
        dir = MFManager->MFLocation - me->GetActorLocation();
    }

    state = EEnemyState::Patrol;
}

void UEnemyFSM::PatrolState(FVector targetDir)
{

    me->AddMovementInput(targetDir.GetSafeNormal());
    FRotator NewRotation = FRotationMatrix::MakeFromX(targetDir).Rotator();
    me->SetActorRotation(NewRotation);

    //플레이어 공격범위 안에 들어오면 공격모드로 전이
    FVector direction = targetP->GetActorLocation() - me->GetActorLocation();
    if (direction.Size() < attackReadyRange) {
        state = EEnemyState::AttackReady;
    }

    else if (enemyCurrentHP == 0) {
        Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode())->countOfSurvivors -= 1;
        state = EEnemyState::Die;
    }

}


void UEnemyFSM::HideState()
{

}

void UEnemyFSM::AttackReadyState()
{
    //무기에 따른 슈팅 반경 설정
    /*if (weaponInfo == 0) shootingRange = shootingRangeShort;
    else if (weaponInfo == 1) shootingRange = shootingRangeMid;
    else if (weaponInfo == 2) shootingRange = shootingRangeLong;*/

    dir = targetP->GetActorLocation() - me->GetActorLocation();
    me->AddMovementInput(dir.GetSafeNormal());

    FRotator NewRotation = FRotationMatrix::MakeFromX(dir).Rotator();
    me->SetActorRotation(NewRotation);

    //플레이어 반경에 들면 멈추고 Shoot모드로 전이
    float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());
    if (distance <= shootingRange) {
        state = EEnemyState::ShootReady;
    }

    else if (enemyCurrentHP == 0) {
        Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode())->countOfSurvivors -= 1;
        state = EEnemyState::Die;
    }

}



void UEnemyFSM::ShootState()
{
    FVector directionToPlayer = targetP->GetActorLocation() - me->GetActorLocation();
    FRotator NewRotation = FRotationMatrix::MakeFromX(directionToPlayer).Rotator();
    me->SetActorRotation(NewRotation);


    //0.7초마다 발사
    currentTime += GetWorld()->GetDeltaSeconds();
    if (currentTime > 0.7) {
        startShooting();
        UGameplayStatics::PlaySound2D(GetWorld(), fireSFX);
        currentTime = 0;
    }
   /* shootingTime += GetWorld()->GetDeltaSeconds();
    if (shootingTime > 2) {
        moveToLR();
        shootingTime = 0;
    }*/
    float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());

    //공격 범위 벗어나면 patrol모드로 전이
    if (distance > attackReadyRange) {
        //GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        state = EEnemyState::GetTarget;

    }

    //체력이 30이하면 escape 모드로 전이
    else if (enemyCurrentHP <= 30) {
        //GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        state = EEnemyState::Escape;
    }

    else if (enemyCurrentHP == 0) {
        Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode())->countOfSurvivors -= 1;
        state = EEnemyState::Die;
    }
}

void UEnemyFSM::DamageState()
{

    enemyCurrentHP -= 10;

    if (enemyCurrentHP == 0) {
        Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode())->countOfSurvivors -= 1;
        state = EEnemyState::Die;
    }
}


void UEnemyFSM::EscapeState()
{
    //플레이어와 반대 방향으로 이동
    dir = me->GetActorLocation() - targetP->GetActorLocation();
    me->AddMovementInput(dir.GetSafeNormal());
    FRotator NewRotation = FRotationMatrix::MakeFromX(dir).Rotator();
    me->SetActorRotation(NewRotation);

    // 일정 거리 이상 멀어졌을 시 patrol 모드로 전이
    float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());
    if (distance > escapeRange) {
        state = EEnemyState::GetTarget;
    }

    else if (enemyCurrentHP == 0) {
        Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode())->countOfSurvivors -= 1;
        state = EEnemyState::Die;
    }
}

void UEnemyFSM::DieState()
{

    me->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    // Mandol 추가
    auto playerController = GetWorld()->GetFirstPlayerController();
    auto player = Cast<ABSPlayer>(playerController->GetCharacter());
    player->killCount += 1;
    player->aliveCount -= 1;

    //me->Destroy();
}



void UEnemyFSM::startShooting()
{
    FHitResult outHit;

    FVector Start = me->GetActorLocation(); // 레이캐스트의 시작점
    FVector End = Start + me->GetActorForwardVector() * 100000; // 레이캐스트의 종료점

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(me); // 현재 액터는 충돌 검사에서 무시

    // 레이캐스트를 수행하고 충돌 정보를 outHit에 저장.
    bool bIsHit = GetWorld()->LineTraceSingleByChannel(outHit, Start, End, ECC_Visibility, CollisionParams);

    if (bIsHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("bls Hit True"));
        // 충돌한 액터를 처리
        AActor* HitActor = outHit.GetActor();
        if (HitActor)
        {
            // 충돌한 액터가 적인지 확인
            ABSPlayer* playerActor = Cast<ABSPlayer>(HitActor);
            if (playerActor)
            {
                int hitRate = rand() % 10;
                if (hitRate < 4) {
                    //플레이어 damage 처리
                    playerActor->onDamage();
                }

            }
        }
    }
}

void UEnemyFSM::moveToLR()
{
    // 왼쪽으로 이동할 양을 결정하는 벡터입니다.
    FVector Movement = FVector(-1.0f, 0.0f, 0.0f); // X 축 방향으로 -1만큼 이동합니다.
    me->AddMovementInput(Movement.GetSafeNormal());
    // 이동에 필요한 속도를 계산합니다.
    //FVector DeltaLocation = Movement * 10000 * GetWorld()->GetDeltaSeconds();

    //// 현재 액터의 위치를 가져옵니다.
    //FVector NewLocation = me->GetActorLocation();

    //// 새로운 위치를 계산합니다.
    //NewLocation += DeltaLocation;

    //// 액터의 위치를 변경합니다.
    //me->SetActorLocation(NewLocation);
}

void UEnemyFSM::MoveToRandomLocation()
{
}

void UEnemyFSM::SetTargetAndAttack(ACharacter* TargetCharacter)
{

}

bool UEnemyFSM::GetRandomChasePoint(float radius, FVector& outLoc)
{
    auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    FNavLocation loc;
    bool result = ns->GetRandomReachablePointInRadius(me->GetActorLocation(), radius, loc);
    if (result) {
        outLoc = loc.Location;
    }
    return result;
}