// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetLooping(false);

	fallRate = 400.0f;
	gravity = 4.4f;

	FMath::SRandInit(time(0));
	setActive(false);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	isFalling = true;
	moveTimer = jumpDelay;
}

void ABaseEnemy::chooseLeftOrRight()
{
	m_goRight = FMath::RandBool();

}

void ABaseEnemy::fall(float deltaTime)
{
	FVector newDir = FVector(0.0f, 0.0f, fallRate * deltaTime);
	SetActorLocation(GetActorLocation() - newDir);

	fallRate += gravity;
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isFalling) 
	{
		fall(DeltaTime);
	}
	else
	{
		moveTimer -= DeltaTime;
		if (moveTimer <= 0)
		{
			Jump();
			moveTimer = jumpDelay;
		}
	}
	if (GetActorLocation().Z < -700)
	{
		readyToDie = true;
		setActive(false);
	}
}

void ABaseEnemy::Jump()
{
	if (!b_isJumping)
	{
		b_isJumping = true;

		//play animation
		Sprite->PlayFromStart();

		m_initialPos = GetActorLocation();

		chooseLeftOrRight();

		//start time line for the jump curve
		if(Timeline != nullptr)
			Timeline->PlayFromStart();
	}
}

void ABaseEnemy::JumpLerp(float time, FVector direction)
{
	FVector newPos = m_initialPos + direction;

	SetActorLocation(FMath::Lerp(m_initialPos, newPos, time));
}

void ABaseEnemy::StopFalling()
{
	isFalling = false;
	fallRate = 400.0;
}

void ABaseEnemy::respawn(FVector spawnPoint)
{
	isFalling = true;
	fallRate = 400.0f;
	readyToDie = false;
	SetActorLocation(spawnPoint);
	setActive(true);
}

void ABaseEnemy::setActive(bool active)
{
	if (this != NULL) {
		
		SetActorHiddenInGame(!active);
		SetActorEnableCollision(active);
		SetActorTickEnabled(active);
	}
}

