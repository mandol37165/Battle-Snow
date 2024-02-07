// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "BSPlayer.h"
#include "Enemy.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MFManager.h"
#include "EngineUtils.h"

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
	
	//�ʱ� ��� getTarget
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
	case EEnemyState::Attack:
		AttackReadyState();
		break;
	case EEnemyState::Shoot:
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

void UEnemyFSM::PatrolState(FVector DIR)
{	
	state = EEnemyState::Patrol;
	me->AddMovementInput(DIR.GetSafeNormal());

	//�÷��̾� ���ݹ��� �ȿ� ������ ���ݸ��� ����
	FVector direction = targetP->GetActorLocation() - me->GetActorLocation();
	if (direction.Size() < attackReadyRange) {
		state = EEnemyState::Attack;
	}

}


void UEnemyFSM::AttackReadyState()
{
	
	dir = targetP->GetActorLocation() - me->GetActorLocation();

	//���⿡ ���� ���� �ݰ� ����
	/*if (weaponInfo == 0) shootingRange = shootingRangeShort;
	else if (weaponInfo == 1) shootingRange = shootingRangeMid;
	else if (weaponInfo == 2) shootingRange = shootingRangeLong;*/

	float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());
	me->AddMovementInput(dir.GetSafeNormal());
	
	//�÷��̾� �ݰ濡 ��� ���߰� Shoot���� ����
	if (distance <= shootingRange) {
		state = EEnemyState::Shoot;
	}
	

	
}



void UEnemyFSM::ShootState()
{
	float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());
	//���� ���� ����� patrol���� ����
	if (distance > attackReadyRange) {
		state = EEnemyState::GetTarget;
	}

	//ü���� 30���ϸ� escape ���� ����
	else if (enemyCurrentHP <= 30) {
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
	//�÷��̾�� �ݴ� �������� �̵�
	dir =  me->GetActorLocation()- targetP->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());


	// ���� �Ÿ� �̻� �־����� �� patrol ���� ����
	float distance = FVector::Distance(targetP->GetActorLocation(), me->GetActorLocation());
	if (distance > escapeRange) {
		state = EEnemyState::GetTarget;
	}
}

void UEnemyFSM::DieState()
{
	// die �ִϸ��̼� ���
}


