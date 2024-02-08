// Fill out your copyright notice in the Description page of Project Settings.


#include "MFManager.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MFPoint.h"
#include "MagneticField.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


// Sets default values
AMFManager::AMFManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMFManager::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> MFPointArr;
	UWorld* World = GetWorld();
    if (World)
    {
        // MFPoint 클래스의 모든 액터를 가져오기
        UGameplayStatics::GetAllActorsOfClass(World, AMFPoint::StaticClass(), MFPointArr);

        // MFPoint 액터 배열이 비어있지 않은 경우에만 랜덤 액터를 선택.
        if (MFPointArr.Num() > 0)
        {
            // 랜덤하게 MFPoint 액터를 선택.
            int32 RandomIndex = FMath::RandRange(0, MFPointArr.Num() - 1);
            AActor* SelectedActor = MFPointArr[RandomIndex];

            if (SelectedActor)
            {
                
                    // MFPoint 액터의 위치값을 가져오기.
                    MFLocation = SelectedActor->GetActorLocation();
                    // 자기장 생성
                   //World->SpawnActor<AMagneticField>(AMagneticField::StaticClass(), MFLocation, FRotator::ZeroRotator);
                   World->SpawnActor<AMagneticField>(magneticFieldFactory, MFLocation, FRotator::ZeroRotator);
                    UE_LOG(LogTemp, Warning, TEXT("complete") );
                
            }
        }
    }
  
}

// Called every frame
void AMFManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
   
}

