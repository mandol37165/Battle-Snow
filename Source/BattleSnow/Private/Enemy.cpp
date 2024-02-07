// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h"
#include "BSPlayer.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Models/BSPlayer/Ch01_nonPBR.Ch01_nonPBR'"));

	if (tempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
	
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	weaponMeshComp0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("weaponMesh0"));
	weaponMeshComp0->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	weaponMeshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("weaponMesh1"));
	weaponMeshComp1->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	weaponMeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("weaponMesh2"));
	weaponMeshComp2->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//weapon이 0 : 단거리 / 1: 중거리 / 2: 장거리
	
	ConstructorHelpers::FObjectFinder<UStaticMesh>weaponMesh0(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SG/SPAS12/SPAS12_Fix.SPAS12_Fix'"));
	if (weaponMesh0.Succeeded()) {
			weaponMeshComp0->SetStaticMesh(weaponMesh0.Object);
			weaponMeshComp0->SetRelativeLocationAndRotation(FVector(0, 52.5, 115), FRotator(0, 90, 0));
			weaponMeshComp0->SetRelativeScale3D(FVector(0.7,1.2,1.2));
			weaponMeshComp0->SetupAttachment(GetMesh());
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh>weaponMesh1(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/AR/AK47/AK47.AK47'"));
	if (weaponMesh1.Succeeded()) {
			weaponMeshComp1->SetStaticMesh(weaponMesh1.Object);
			weaponMeshComp1->SetRelativeLocationAndRotation(FVector(-5.5,67.5, 127.5), FRotator(0, 90, 0));
			weaponMeshComp1->SetRelativeScale3D(FVector(1.2, 1.5, 1.5));
			weaponMeshComp1->SetupAttachment(GetMesh());
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>weaponMesh2(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SR/RSASS/RSASS_fix.RSASS_fix'"));
	if (weaponMesh2.Succeeded()) {
			weaponMeshComp2->SetStaticMesh(weaponMesh2.Object);
			weaponMeshComp2->SetRelativeLocationAndRotation(FVector(-5.5, 67.5, 130), FRotator(0, 90, 0));
			weaponMeshComp2->SetRelativeScale3D(FVector(1, 1.5, 1.3));
			weaponMeshComp2->SetupAttachment(GetMesh());
	}
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	
	UStaticMeshComponent* comps[] = { weaponMeshComp0 , weaponMeshComp1,weaponMeshComp2};
	int randValue = rand() % 3;
	for (int i = 0; i < 3; i++)
	{
		comps[i]->SetVisibility(i == randValue);
	}
	//무기정보 저장
	weaponNum = randValue;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}







