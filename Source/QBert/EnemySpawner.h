// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEnemy.h"
#include "Containers/Queue.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class QBERT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
		TArray<FVector> spawnLocations;
	float spawnTime = 4.0f;
	float timer = 4.0f;
	bool isCoilyDead = true;
	int turnsToCoily = 2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	class ABaseEnemy* CoilyEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TArray<ABaseEnemy*> inactiveEnemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TArray<ABaseEnemy*> activeEnemies;

	UFUNCTION(BlueprintImplementableEvent, category = Spawn)
	void CoilyDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttemptSpawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Spawn)
	void SpawnEnemy(FVector location);
	UFUNCTION(BlueprintImplementableEvent, Category = Spawn)
	void SpawnCoilyEgg(FVector location);

	UFUNCTION(BlueprintImplementableEvent, Category = Spawn)
	void DeleteEnemies();

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void resetSpawns();

	UFUNCTION(BlueprintCallable, Category = Spawn)
		void delaySpawns(float time);

};
