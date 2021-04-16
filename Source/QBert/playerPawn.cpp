// Fill out your copyright notice in the Description page of Project Settings.

#include "playerPawn.h"
#include "Math/Vector.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AplayerPawn::AplayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	isFalling = false;
	fallRate = 200.0f;
	gravity = 16.0f;

	Sprites = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprites"));
	Sprites->SetLooping(false);
	
}

// Called when the game starts or when spawned
void AplayerPawn::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AQBertGameModeBase>(GetWorld()->GetAuthGameMode());
	
	m_row = m_column = 1;
	
}

void AplayerPawn::MoveUpLeft()
{
	if (!b_isJumping)
	{
		dir = UP_LEFT;
		m_row--;
		m_column--;
		Sprites->SetFlipbook(jumpUpLeft);
		Jump();
	}
}

void AplayerPawn::MoveDownLeft()
{
	if (!b_isJumping)
	{
		dir = DOWN_LEFT;
		m_row++;
		Sprites->SetFlipbook(jumpDownLeft);
		Jump();
		
	}
}

void AplayerPawn::MoveUpRight()
{
	if (!b_isJumping)
	{
		dir = UP_RIGHT;
		m_row--;
		Sprites->SetFlipbook(jumpUpRight);
		Jump();
	}
}

void AplayerPawn::MoveDownRight()
{
	if (!b_isJumping)
	{
		dir = DOWN_RIGHT;
		m_row++;
		m_column++;
		Sprites->SetFlipbook(jumpDownRight);
		Jump();
	}
}

void AplayerPawn::fall(float deltaTime)
{
	if (isFalling)
	{
		FVector newDir = FVector(0.0f, 0.0f, fallRate * deltaTime);
		SetActorLocation(GetActorLocation() - newDir);

		fallRate += gravity;

		if (GetActorLocation().Z <= -1000)
		{
			
			fallRate = 300.0f;
			m_column = 1;
			m_row = 1;
			resetEnemies();
			OnDelay();
		}
	}
}


// Called every frame
void AplayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	fall(DeltaTime);
}

// Called to bind functionality to input
void AplayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("UpLeft", IE_Pressed, this, &AplayerPawn::MoveUpLeft);
	PlayerInputComponent->BindAction("UpRight", IE_Pressed, this, &AplayerPawn::MoveUpRight);
	PlayerInputComponent->BindAction("DownLeft", IE_Pressed, this, &AplayerPawn::MoveDownLeft);
	PlayerInputComponent->BindAction("DownRight", IE_Pressed, this, &AplayerPawn::MoveDownRight);
	
}

void AplayerPawn::Jump()
{
	if (!b_isJumping && !isFalling)
	{
		b_isJumping = true;

		//play animation
		Sprites->PlayFromStart();

		m_initialPos = GetActorLocation();

		//start time line for the jump curve
		if (Timeline != nullptr)
			Timeline->PlayFromStart();
	}
}


//lerp in direction set by curves in the blueprint jump time line
void AplayerPawn::JumpLerp(float time, FVector direction)
{
	FVector newPos = m_initialPos + direction;

	SetActorLocation(FMath::Lerp(m_initialPos, newPos, time));
}


void AplayerPawn::resetRowAndColumn()
{
	m_row = 1;
	m_column = 1;
}

