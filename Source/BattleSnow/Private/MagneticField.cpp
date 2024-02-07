// Fill out your copyright notice in the Description page of Project Settings.


#include "MagneticField.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AMagneticField::AMagneticField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	this->SetRootComponent(sphereComp);

	magneticFieldComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("magneticFieldComp"));
	magneticFieldComp->SetupAttachment(RootComponent);

	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName("MageneticField");

	magneticFieldComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (tempMesh.Succeeded()) {
		magneticFieldComp->SetStaticMesh(tempMesh.Object);

		ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/ddoza/Material/MagneticField.MagneticField' "));
		if (tempMat.Succeeded()) {
			magneticFieldComp->SetMaterial(0, tempMat.Object);
			magneticFieldComp->SetRelativeLocationAndRotation(FVector(-290, 0, 0), FRotator(0, 0, 0));
			magneticFieldComp->SetRelativeScale3D(FVector(100, 100, 100));
			magneticFieldComp->SetupAttachment(sphereComp);
		}
	}

}

// Called when the game starts or when spawned
void AMagneticField::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMagneticField::makeMFSmall,5.0f, true);


}

// Called every frame
void AMagneticField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMagneticField::makeMFSmall()
{
	
		FVector targetScale;
		FVector actorScale = this->GetActorScale3D();
		//5√ ∏∂¥Ÿ
		targetScale.X = actorScale.X * 0.90;
		targetScale.Y = actorScale.Y * 0.90;
		targetScale.Z = 1.0;

		SetActorScale3D(FMath::Lerp<FVector>(actorScale, targetScale, 0.1));
		UE_LOG(LogTemp, Warning, TEXT("Make it small"));
	
}

