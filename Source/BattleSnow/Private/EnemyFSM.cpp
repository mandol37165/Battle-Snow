// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "BSPlayer.h"
#include "Enemy.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MFManager.h"
#include "EngineUtils.h"
#include "ARBulletActor.h"
#include "TimerManager.h"

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
	
	//초기 모드 getTarget
	state = EEnemyState::GetTarget;

	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	switch (state)
	{
	case EEnemyState::GetTarget:
		GetTargetState();
		break;
	case EEnemyState::Patrol:
		PatrolState(dir);
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

void UEnemyFSM::PatrolState(FVector DIR)
{	
	state = EEnemyState::Patrol;
	me->AddMovementInput(DIR.GetSafeNormal());

	//플레이어 공격범위 안에 들어오면 공격모드로 전이
	FVector direction = targetP->GetActorLocation() - me->GetActorLocation();
	if (direction.Size() < attackReadyRange) {
		state = EEnemyState::AttackReady;
	}

}


void UEnemyFSM::AttackReadyState()
{
	
	dir = targetP->GetActorLocation() - me->GetActorLocation();

	//무기에 따른 슈팅 반경 설정
	/*if (weaponInfo == 0) shootingRange = shootingRangeShort;
	else if (weaponInfo == 1) shootingRange = shootingRangeMid;
	else if (weaponInfo == 2) shootingRange = shootingRangeLong;*/

	float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());
	me->AddMovementInput(dir.GetSafeNormal());
	
	//플레이어 반경에 들면 멈추고 Shoot모드로 전이
	if (distance <= shootingRange) {
		state = EEnemyState::ShootReady;
	}
	

	
}



void UEnemyFSM::ShootState()
{
	FVector directionToPlayer = targetP->GetActorLocation() - me->GetActorLocation();
	FRotator NewRotation= FRotationMatrix::MakeFromX(directionToPlayer).Rotator();
	me->SetActorRotation(NewRotation);

	//0.7초마다 발사
	currentTime += GetWorld()->GetDeltaSeconds();
	if (currentTime > 0.7) {
		startShooting();
		UGameplayStatics::PlaySound2D(GetWorld(), fireSFX);
		currentTime = 0;
	}

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
}

void UEnemyFSM::DamageState()
{
	
	enemyCurrentHP -= 10;

	if (enemyCurrentHP <= 0) {
		state = EEnemyState::Die;
	}
}


void UEnemyFSM::EscapeState()
{
	//플레이어와 반대 방향으로 이동
	dir =  me->GetActorLocation()- targetP->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());
	FRotator NewRotation = FRotationMatrix::MakeFromX(dir).Rotator();
	me->SetActorRotation(NewRotation);

	// 일정 거리 이상 멀어졌을 시 patrol 모드로 전이
	float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());
	if (distance > escapeRange) {
		state = EEnemyState::GetTarget;
	}
}

void UEnemyFSM::DieState()
{
	
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
				UE_LOG(LogTemp, Warning, TEXT("hit actor is player"));
				//플레이어 damage 처리
				playerActor->onDamage();
			}
		}
	}
}

