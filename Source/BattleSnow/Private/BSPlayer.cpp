// Fill out your copyright notice in the Description page of Project Settings.


#include "BSPlayer.h"
#include "Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "ARBulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Enemy.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Core/Public/UObject/NameTypes.h"
#include "EnemyFSM.h"
#include "Engine/EngineTypes.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABSPlayer::ABSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent->SetWorldScale3D(FVector(4.0f));

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, 30, 90));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Models/BSPlayer/Remy.Remy'"));
	// 己傍沁促搁
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.5f));
	}

	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	ak47AttachPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ak47AttachPos"));
	ak47AttachPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempAkMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/AR/AK47/AK47.AK47'"));

	if (tempAkMesh.Succeeded())
	{
			ak47AttachPos->SetStaticMesh(tempAkMesh.Object);
			ak47AttachPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("AK47Socket")));
			ak47AttachPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			ak47AttachPos->SetVisibility(false);
	}

	ak47ShoulderPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AK47ShoulderPos"));
	ak47ShoulderPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempAKShoulderMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/AR/AK47/AK47.AK47'"));

	if (tempAKShoulderMesh.Succeeded())
	{
		ak47ShoulderPos->SetStaticMesh(tempAKShoulderMesh.Object);
		ak47ShoulderPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("AK47ShoulderSocket"));
		ak47ShoulderPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ak47ShoulderPos->SetVisibility(false);
	}

	ak47LSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AK47LSPos"));
	ak47LSPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempAK47LSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/AR/AK47/AK47.AK47'"));

	if (tempAK47LSMesh.Succeeded())
	{
		ak47LSPos->SetStaticMesh(tempAK47LSMesh.Object);
		ak47LSPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("AK47LSSocket"));
		ak47LSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ak47LSPos->SetVisibility(false);
	}

	benelliM4HandPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BenelliM4HandPos"));
	benelliM4HandPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBenelliMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SG/Benelli_M4/Benelli_M4.Benelli_M4'"));

	if (tempBenelliMesh.Succeeded())
	{
		benelliM4HandPos->SetStaticMesh(tempBenelliMesh.Object);
		benelliM4HandPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("BenelliHandSocket")));
		benelliM4HandPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		benelliM4HandPos->SetVisibility(false);
	}

	benelliM4RSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BenelliM4RSPos"));
	benelliM4RSPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBenelliRSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SG/Benelli_M4/Benelli_M4.Benelli_M4'"));

	if (tempBenelliRSMesh.Succeeded())
	{
		benelliM4RSPos->SetStaticMesh(tempBenelliRSMesh.Object);
		benelliM4RSPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BenelliM4RSSocket"));
		benelliM4RSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		benelliM4RSPos->SetVisibility(false);
	}

	benelliM4LSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BenelliM4LSPos"));
	benelliM4LSPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBenelliLSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SG/Benelli_M4/Benelli_M4.Benelli_M4'"));

	if (tempBenelliLSMesh.Succeeded())
	{
		benelliM4LSPos->SetStaticMesh(tempBenelliLSMesh.Object);
		benelliM4LSPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BenelliM4LSSocket"));
		benelliM4LSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		benelliM4LSPos->SetVisibility(false);
	}
	
	barretHandPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("barretHandPos"));
	barretHandPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBarretMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SR/Barret/Barret_Fix.Barret_Fix'"));

	if (tempBarretMesh.Succeeded())
	{
		barretHandPos->SetStaticMesh(tempBarretMesh.Object);
		barretHandPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("BarretHandSocket")));
		barretHandPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		barretHandPos->SetVisibility(false);
	}

	barretRSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarretRSPos"));
	barretRSPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBarretRSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SR/Barret/Barret_Fix.Barret_Fix'"));

	if (tempBarretRSMesh.Succeeded())
	{
		barretRSPos->SetStaticMesh(tempBarretRSMesh.Object);
		barretRSPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BarretRSSocket"));
		barretRSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		barretRSPos->SetVisibility(false);
	}

	barretLSPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarretLSPos"));
	barretLSPos->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBarretLSMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Weapon/SR/Barret/Barret_Fix.Barret_Fix'"));

	if (tempBarretLSMesh.Succeeded())
	{
		barretLSPos->SetStaticMesh(tempBarretLSMesh.Object);
		barretLSPos->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BarretLSSocket"));
		barretLSPos->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		barretLSPos->SetVisibility(false);
	}

	firePos = CreateDefaultSubobject<UArrowComponent>(TEXT("firePos"));
	firePos->SetupAttachment(ak47AttachPos);
	//firePos->SetRelativeLocationAndRotation(FVector(-17, 60, 140),FRotator(0, 90 ,0));
	firePos->SetRelativeLocation(FVector(35, -0.5f, 5.5f));
}

// Called when the game starts or when spawned
	void ABSPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerCurrentHP = playerMaxHP;

	inMfield = true;
}

// Called every frame
void ABSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();

	Zoom();

	PlayerisDead();
}

// Called to bind functionality to input
void ABSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ABSPlayer::OnAxisVertical);

	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &ABSPlayer::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &ABSPlayer::OnAxisTurnYaw);

	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &ABSPlayer::OnAxisLookupPitch);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABSPlayer::OnActionJump);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ABSPlayer::OnActionFire);

	PlayerInputComponent->BindAction(TEXT("AimingAndZoom"), IE_Pressed, this, &ABSPlayer::OnActionAiming);

	PlayerInputComponent->BindAction(TEXT("AimingAndZoom"), IE_Pressed, this, &ABSPlayer::OnActionZoomIn);

	PlayerInputComponent->BindAction(TEXT("AimingAndZoom"), IE_Released, this, &ABSPlayer::OnActionZoomOut);

}

void ABSPlayer::PlayerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{

}

//void ABSPlayer::OnPlayerCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//
//}

void ABSPlayer::Move()
{
	FTransform trans = GetActorTransform();
	AddMovementInput(trans.TransformVector(direction));
}

void ABSPlayer::OnAxisVertical(float value)
{
	if (false == bOnWidget)
	{
		direction.X = value * 5;
	}
	else
	{
		direction.X = 0;
	}
}

void ABSPlayer::OnAxisHorizontal(float value)
{
	if(false == bOnWidget)
	{
		direction.Y = value * 5;
	}
	else
	{
		direction.Y = 0;
	}
}

void ABSPlayer::OnAxisTurnYaw(float value)
{
	if (false == bOnWidget)
	{
		AddControllerYawInput(value);
	}
	else
	{
		return;
	}
}

void ABSPlayer::OnAxisLookupPitch(float value)
{
	if (false == bOnWidget)
	{
		AddControllerPitchInput(value);
	}
	else
	{
		return;
	}
}

void ABSPlayer::OnActionJump()
{
	bIsJumping = true;
	Jump();
}

void ABSPlayer::OnActionFire()
{
	if (bIsEquipRifle && bIsEquipRifleOnHand)
	{
		bIsAiming = true;

		if (checkCurrentWeaponIndex == 0) 
		{
			if (bHasARAmmo && currentARAmmoAmount > 0)
			{
				bIsFire = true;

				UGameplayStatics::PlaySound2D(GetWorld(), fireSFX);

				currentARAmmoAmount--;

				// #### Bullet Spawn ####
				//FTransform t = firePos->GetComponentTransform();
				//FTransform t1 = ak47AttachPos->GetSocketTransform(FName("AKMuzzle"));

				//GetWorld()->SpawnActor<AARBulletActor>(bulletFactory, t1);


				if (false == bOnWidget)
				{
					FHitResult outHit;
					FVector start = cameraComp->GetComponentLocation();
					FVector end = start + cameraComp->GetForwardVector() * 100000;
					FCollisionQueryParams params;
					params.AddIgnoredActor(this);

					bool bReturnValue = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECollisionChannel::ECC_Visibility, params);

					if (bReturnValue)
					{
						//DrawDebugLine(GetWorld(), outHit.TraceStart, outHit.ImpactPoint, FColor::Red, false, 10);

						//UPrimitiveComponent* hitComp = outHit.GetComponent();

						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expVFX, outHit.ImpactPoint);

						AActor* HitActor = outHit.GetActor();

						AEnemy* enemyActor = Cast<AEnemy>(HitActor);
						if (enemyActor)
						{
							auto enemy = outHit.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));

							if (enemy)
							{
								auto enemyFSM = Cast<UEnemyFSM>(enemy);

								// #### Enemy 单固瘤 贸府 ####
								enemyFSM->DamageState();
							}
						}
					}
				}
				if (currentARAmmoAmount <= 0)
				{
					bHasARAmmo = false;
				}
			}
		}
		else if (checkCurrentWeaponIndex == 1)
		{
			if (bHasSGAmmo && currentSGAmmoAmount > 0)
			{
				bIsFire = true;

				UGameplayStatics::PlaySound2D(GetWorld(), fireSFX);

				currentSGAmmoAmount--;

				// #### Bullet Spawn ####
				//FTransform t = firePos->GetComponentTransform();
				//FTransform t1 = ak47AttachPos->GetSocketTransform(FName("AKMuzzle"));

				//GetWorld()->SpawnActor<AARBulletActor>(bulletFactory, t1);


				if (false == bOnWidget)
				{
					FHitResult outHit;
					FVector start = cameraComp->GetComponentLocation();
					FVector end = start + cameraComp->GetForwardVector() * 100000;
					FCollisionQueryParams params;
					params.AddIgnoredActor(this);

					bool bReturnValue = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECollisionChannel::ECC_Visibility, params);

					if (bReturnValue)
					{
						//DrawDebugLine(GetWorld(), outHit.TraceStart, outHit.ImpactPoint, FColor::Red, false, 10);

						//UPrimitiveComponent* hitComp = outHit.GetComponent();

						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expVFX, outHit.ImpactPoint);

						AActor* HitActor = outHit.GetActor();

						AEnemy* enemyActor = Cast<AEnemy>(HitActor);
						if (enemyActor)
						{
							auto enemy = outHit.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));

							if (enemy)
							{
								auto enemyFSM = Cast<UEnemyFSM>(enemy);

								UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expVFX, outHit.ImpactPoint);

								// #### Enemy 单固瘤 贸府 ####
								enemyFSM->DamageState();
							}
						}
					}
				}
				if (currentSGAmmoAmount <= 0)
				{
					bHasSGAmmo = false;
				}
			}
		}
		else if (checkCurrentWeaponIndex == 2)
		{
			if (bHasSRAmmo && currentSRAmmoAmount > 0)
			{
				bIsFire = true;

				UGameplayStatics::PlaySound2D(GetWorld(), fireSFX);

				currentSRAmmoAmount--;

				// #### Bullet Spawn ####
				//FTransform t = firePos->GetComponentTransform();
				//FTransform t1 = ak47AttachPos->GetSocketTransform(FName("AKMuzzle"));

				//GetWorld()->SpawnActor<AARBulletActor>(bulletFactory, t1);


				if (false == bOnWidget)
				{
					FHitResult outHit;
					FVector start = cameraComp->GetComponentLocation();
					FVector end = start + cameraComp->GetForwardVector() * 100000;
					FCollisionQueryParams params;
					params.AddIgnoredActor(this);

					bool bReturnValue = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECollisionChannel::ECC_Visibility, params);

					if (bReturnValue)
					{
						//DrawDebugLine(GetWorld(), outHit.TraceStart, outHit.ImpactPoint, FColor::Red, false, 10);

						//UPrimitiveComponent* hitComp = outHit.GetComponent();

						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expVFX, outHit.ImpactPoint);

						AActor* HitActor = outHit.GetActor();

						AEnemy* enemyActor = Cast<AEnemy>(HitActor);
						if (enemyActor)
						{
							auto enemy = outHit.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));

							if (enemy)
							{
								auto enemyFSM = Cast<UEnemyFSM>(enemy);

								

								// #### Enemy 单固瘤 贸府 ####
								enemyFSM->DamageState();
							}
						}
					}
				}
				if (currentSRAmmoAmount <= 0)
				{
					bHasSRAmmo = false;
				}
			}
		}
	}
}

void ABSPlayer::PlayerisDead()
{
	if (playerCurrentHP <= 0)
	{
		isPlayerDead = true;
		this->PlayAnimMontage(playerDeadMontage);
	}
}

void ABSPlayer::CheckMFIn()
{

}

void ABSPlayer::TakeDamageOutMF()
{
	if (false == inMfield) 
	{
		double Seconds = FPlatformTime::Seconds();
		int64 curMilSec = static_cast<int64>(Seconds * 1000);

		static int64 milliseconds = 0;

		if (curMilSec - milliseconds > 500)
		{
			playerCurrentHP -= 0.5;
		}
		
	}
}

void ABSPlayer::OnActionAiming()
{
	if (bIsEquipRifle && bIsEquipRifleOnHand)
	{
		//if (false == bIsAiming)
		//{
		//	bIsAiming = true;
		//}
		//else
		//{
		//	bIsAiming = false;
		//}
	}
}

void ABSPlayer::OnActionZoomIn()
{
	if (bIsAiming && checkCurrentWeaponIndex == 0)
	{
		targetFOV = 50;
	}
	else if (bIsAiming && checkCurrentWeaponIndex == 1)
	{
		targetFOV = 50;
	}
	else if (bIsAiming && checkCurrentWeaponIndex == 2)
	{
		targetFOV = 20;
	}
	else
	{
		return;
	}
}

void ABSPlayer::OnActionZoomOut()
{
	targetFOV = 90;
}

void ABSPlayer::Zoom()
{
	cameraComp->FieldOfView = FMath::Lerp<float>(cameraComp->FieldOfView, targetFOV, GetWorld()->GetDeltaSeconds() * 6);
}

void ABSPlayer::onDamage()
{
	playerCurrentHP -= 10;

	if (playerCurrentHP <= 0)
	{
		PlayerisDead();
	}
}

