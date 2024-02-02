// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "BSPlayer.h"
#include "Enemy.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"



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

	me = Cast<AEnemy>(GetOwner());
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (state)
	{
	case EEnemyState::Idle:
		IdleState();
			break;
	case EEnemyState::Move:
		MoveState();
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
	case EEnemyState::Die:
		DieState();
		break;
	
	}
}

void UEnemyFSM::IdleState()
{
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime) {
		state = EEnemyState::Move;
		currentTime = 0;
	}

}

void UEnemyFSM::MoveState()
{
	FVector dir = target->GetActorLocation() - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());

	if (dir.Size() < attackRange) {
		state = EEnemyState::Attack;
	}
}

void UEnemyFSM::AttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime) {
		currentTime = 0;
	}
}

void UEnemyFSM::DamageState()
{
}

void UEnemyFSM::DieState()
{
}

