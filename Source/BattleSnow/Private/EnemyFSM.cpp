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
    // ���� ���� ��������
    me = Cast<AEnemy>(GetOwner());

    /*if (me) {
       weaponInfo = me->weaponNum;
       UE_LOG(LogTemp, Warning, TEXT("%s"),weaponInfo );
    }*/
    GetRandomChasePoint(SearchRadius, chasePoint);
    //�ʱ� ��� getTarget

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
        //�÷��̾�� Ÿ�� ����
        dir = targetP->GetActorLocation() - me->GetActorLocation();
    }

    else if (randValue == 1) {

        AMFManager* MFManager = Cast<AMFManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMFManager::StaticClass()));
        //for (TActorIterator<AMFManager> it(GetWorld()); it; ++it){MFManager = *it;
        //�ڱ��� �߽��� ��ǥ������ ����
        dir = MFManager->MFLocation - me->GetActorLocation();
    }

    state = EEnemyState::Patrol;
}

void UEnemyFSM::PatrolState(FVector targetDir)
{

    me->AddMovementInput(targetDir.GetSafeNormal());
    FRotator NewRotation = FRotationMatrix::MakeFromX(targetDir).Rotator();
    me->SetActorRotation(NewRotation);

    //�÷��̾� ���ݹ��� �ȿ� ������ ���ݸ��� ����
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
    //���⿡ ���� ���� �ݰ� ����
    /*if (weaponInfo == 0) shootingRange = shootingRangeShort;
    else if (weaponInfo == 1) shootingRange = shootingRangeMid;
    else if (weaponInfo == 2) shootingRange = shootingRangeLong;*/

    dir = targetP->GetActorLocation() - me->GetActorLocation();
    me->AddMovementInput(dir.GetSafeNormal());

    FRotator NewRotation = FRotationMatrix::MakeFromX(dir).Rotator();
    me->SetActorRotation(NewRotation);

    //�÷��̾� �ݰ濡 ��� ���߰� Shoot���� ����
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


    //0.7�ʸ��� �߻�
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

    //���� ���� ����� patrol���� ����
    if (distance > attackReadyRange) {
        //GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        state = EEnemyState::GetTarget;

    }

    //ü���� 30���ϸ� escape ���� ����
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
    //�÷��̾�� �ݴ� �������� �̵�
    dir = me->GetActorLocation() - targetP->GetActorLocation();
    me->AddMovementInput(dir.GetSafeNormal());
    FRotator NewRotation = FRotationMatrix::MakeFromX(dir).Rotator();
    me->SetActorRotation(NewRotation);

    // ���� �Ÿ� �̻� �־����� �� patrol ���� ����
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
    // Mandol �߰�
    auto playerController = GetWorld()->GetFirstPlayerController();
    auto player = Cast<ABSPlayer>(playerController->GetCharacter());
    player->killCount += 1;
    player->aliveCount -= 1;

    //me->Destroy();
}



void UEnemyFSM::startShooting()
{
    FHitResult outHit;

    FVector Start = me->GetActorLocation(); // ����ĳ��Ʈ�� ������
    FVector End = Start + me->GetActorForwardVector() * 100000; // ����ĳ��Ʈ�� ������

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(me); // ���� ���ʹ� �浹 �˻翡�� ����

    // ����ĳ��Ʈ�� �����ϰ� �浹 ������ outHit�� ����.
    bool bIsHit = GetWorld()->LineTraceSingleByChannel(outHit, Start, End, ECC_Visibility, CollisionParams);

    if (bIsHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("bls Hit True"));
        // �浹�� ���͸� ó��
        AActor* HitActor = outHit.GetActor();
        if (HitActor)
        {
            // �浹�� ���Ͱ� ������ Ȯ��
            ABSPlayer* playerActor = Cast<ABSPlayer>(HitActor);
            if (playerActor)
            {
                int hitRate = rand() % 10;
                if (hitRate < 4) {
                    //�÷��̾� damage ó��
                    playerActor->onDamage();
                }

            }
        }
    }
}

void UEnemyFSM::moveToLR()
{
    // �������� �̵��� ���� �����ϴ� �����Դϴ�.
    FVector Movement = FVector(-1.0f, 0.0f, 0.0f); // X �� �������� -1��ŭ �̵��մϴ�.
    me->AddMovementInput(Movement.GetSafeNormal());
    // �̵��� �ʿ��� �ӵ��� ����մϴ�.
    //FVector DeltaLocation = Movement * 10000 * GetWorld()->GetDeltaSeconds();

    //// ���� ������ ��ġ�� �����ɴϴ�.
    //FVector NewLocation = me->GetActorLocation();

    //// ���ο� ��ġ�� ����մϴ�.
    //NewLocation += DeltaLocation;

    //// ������ ��ġ�� �����մϴ�.
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