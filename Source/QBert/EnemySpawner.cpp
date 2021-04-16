// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include <UObject/UObjectGlobals.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemySpawner::Tick(float DeltaTime)
{
	timer -= DeltaTime;
	if (timer <= 0.0f)
	{
		AttemptSpawnEnemy();
	}
	DeleteEnemies();
}

void AEnemySpawner::resetSpawns()
{
	timer = spawnTime;
	isCoilyDead = true;
}

void AEnemySpawner::delaySpawns(float time)
{
	timer += time;
}

void AEnemySpawner::AttemptSpawnEnemy()
{
	FVector spawnPoint = spawnLocations[rand() % spawnLocations.Num()];
	timer = spawnTime;

	//do we spawn coily
	if (isCoilyDead)
	{
		turnsToCoily--;
		if (turnsToCoily <= 0)
		{
			//spawn coily and leave
			SpawnCoilyEgg(spawnPoint);
			isCoilyDead = false;
			turnsToCoily = rand() % 2 + 2; //2 or 3
			return;
		}
	}

	SpawnEnemy(spawnPoint);
}
