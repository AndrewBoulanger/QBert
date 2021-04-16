// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TimelineComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS()
class QBERT_API ABaseEnemy : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		UTimelineComponent* Timeline;

	UFUNCTION(BlueprintCallable, Category = Spawning)
	void setActive(bool active);

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = sprite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* Sprite;

	FVector m_initialPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool b_isJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float fallRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool isFalling;
	float gravity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool m_goRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	bool readyToDie = false;
	
	virtual void BeginPlay() override;

	void chooseLeftOrRight();

	void fall(float deltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float jumpDelay;
	float moveTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//starts the time line in the eventGraph
	UFUNCTION(BlueprintCallable, Category = movement)
		void Jump();

	UFUNCTION(BlueprintCallable, Category = movement)
		void JumpLerp(float time, FVector direction);
	UFUNCTION(BlueprintCallable, Category = movement)
		void StopFalling();
	UFUNCTION(BlueprintCallable, Category = Spawning)
	void respawn(FVector spawnPoint);

	UFUNCTION(BlueprintCallable, Category = Spawning)
		bool GetIsDead(){return readyToDie;}
};
