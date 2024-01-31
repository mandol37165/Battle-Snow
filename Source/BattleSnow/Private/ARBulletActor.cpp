// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"

// Sets default values
AARBulletActor::AARBulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsuleComp"));
	SetRootComponent(capsuleComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject< UProjectileMovementComponent >(TEXT("movementComp"));

	movementComp->InitialSpeed = 2000.0f;
	movementComp->MaxSpeed = 2000.0f;

	meshComp->SetWorldScale3D(FVector(0.25f));
	//capsuleComp->SetSphereRadius(12.5f);
}

// Called when the game starts or when spawned
void AARBulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle timerHandle;
	//GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ABulletActor::AutoDestroy, 1, false);
	GetWorld()->GetTimerManager().SetTimer(timerHandle,
		FTimerDelegate::CreateLambda([this]()-> void {this->Destroy(); }), 5, false);
}

// Called every frame
void AARBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARBulletActor::AutoDestory()
{
	this->Destroy();
}

