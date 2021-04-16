// Fill out your copyright notice in the Description page of Project Settings.


#include "Coily.h"

// Sets default values
ACoily::ACoily()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isFalling = false;
	fallRate = 200.0f;
	gravity = 16.0f;
	moveTimer = jumpDelay;

	Sprites = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprites"));
	Sprites->SetLooping(false);
}

void ACoily::setActive(bool active)
{
	if (this != NULL) {

		SetActorHiddenInGame(!active);
		SetActorEnableCollision(active);
		SetActorTickEnabled(active);
	}
}

// Called when the game starts or when spawned
void ACoily::BeginPlay()
{
	Super::BeginPlay();

}

void ACoily::setDir()
{
	//jump down when coilies row is < than Qberts (further up) 
	if (m_row < m_targetRow && m_row != 7)
	{
		UpOrDown(false);
		
	}
	//jump down when coilies row is > than Qberts (further down) 
	else if(m_row > m_targetRow || m_row == 7 )
	{
		UpOrDown(true);
	}
	else //random
	{
		UpOrDown(FMath::RandBool());
	}
}

bool ACoily::NeedsToGoLeft()
{
	float y = (float)m_col / ((float)m_row + 1.0f);
	float target_y = (float)m_targetCol / ((float)m_targetRow + 1.0f);

	if (y > target_y)   //coily y > Qbert y, need to go left
	{
		return true;
	}
	else if (y < target_y)
	{
		return false;
	}
	else
		return FMath::RandBool();
}

void ACoily::UpOrDown(bool goingUp)
{
	if (goingUp)
	{
		if (NeedsToGoLeft())
		{
			dir = UP_LEFT;
			Sprites->SetFlipbook(jumpUpLeft);
			m_row--;
			m_col--;
		}
		else
		{
			dir = UP_RIGHT;
			Sprites->SetFlipbook(jumpUpRight);
			m_row--;
		}
	}
	else
	{
		if (NeedsToGoLeft())
		{
			dir = DOWN_LEFT;
			Sprites->SetFlipbook(jumpDownLeft);
			m_row++;
		}
		else
		{
			dir = DOWN_RIGHT;
			Sprites->SetFlipbook(jumpDownRight);
			m_row++;
			m_col++;
		}
	}
}

void ACoily::fall(float deltaTime)
{
	FVector newDir = FVector(0.0f, 0.0f, fallRate * deltaTime);
	SetActorLocation(GetActorLocation() - newDir);

	fallRate += gravity;
}

// Called every frame
void ACoily::Tick(float DeltaTime)
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
			SettingTarget();
			Jump();
			moveTimer = jumpDelay;
		}
	}
	if (GetActorLocation().Z < -700)
	{
		Despawn();
	}
}

void ACoily::setRowAndCol(int row, int col)
{
	m_row = row;
	m_col = col;
}


void ACoily::SetTargetRowAndCol(int row, int col)
{
	m_targetRow = row;
	m_targetCol = col;
}

void ACoily::Jump()
{
	if (!b_isJumping)
	{
		b_isJumping = true;

		setDir();

		//play animation
		Sprites->PlayFromStart();

		m_initialPos = GetActorLocation();

		//start time line for the jump curve
		if (Timeline != nullptr)
			Timeline->PlayFromStart();
	}
}

void ACoily::JumpLerp(float time, FVector direction)
{
	FVector newPos = m_initialPos + direction;

	SetActorLocation(FMath::Lerp(m_initialPos, newPos, time));
}

void ACoily::StopFalling()
{
	isFalling = false;
	fallRate = 200.0f;
}

void ACoily::SpawnIn(FVector pos)
{
	SetActorLocation(pos);
	setActive(true);
}

void ACoily::Despawn()
{
	setActive(false);
	if (Spawner != nullptr)
	{
		Spawner->isCoilyDead = true;  //fix this later its bad code to make this public
		Spawner->timer = 5.0f;
		Spawner->CoilyDeath();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("spawner not linked to coily"));
	}
}

