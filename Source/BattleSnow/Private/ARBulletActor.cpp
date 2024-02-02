// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h"


// Sets default values
AARBulletActor::AARBulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject< UProjectileMovementComponent >(TEXT("movementComp"));

	movementComp->InitialSpeed = 1000000.0f;
	movementComp->MaxSpeed = 1000000.0f;

	sphereComp->SetCollisionProfileName(TEXT("BlockAll"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	sphereComp->SetSphereRadius(0.1f);
	meshComp->SetWorldScale3D(FVector(0.2f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));

	meshComp->SetStaticMesh(tempStaticMesh.Object);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> tempMatTest(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Mandol/Material/MI_TestBullet.MI_TestBullet'"));

	meshComp->GetStaticMesh()->SetMaterial(0, tempMatTest.Object);
}

// Called when the game starts or when spawned
void AARBulletActor::BeginPlay()
{
	Super::BeginPlay();

	movementComp->SetUpdatedComponent(sphereComp);
	
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

