// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemySpawner.h"
#include "Components/TimelineComponent.h"
#include "playerPawn.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coily.generated.h"


UCLASS()
class QBERT_API ACoily : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoily();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		UTimelineComponent* Timeline;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int m_row;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int m_col;
	int m_targetRow;
	int m_targetCol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		TEnumAsByte<direction> dir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
		UPaperFlipbookComponent* Sprites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
		UPaperFlipbook* jumpDownLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
		UPaperFlipbook* jumpUpLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
		UPaperFlipbook* jumpDownRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
		UPaperFlipbook* jumpUpRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		AEnemySpawner* Spawner;

	UFUNCTION(BlueprintCallable, Category = Spawning)
	void setActive(bool active);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float jumpDelay;
	float moveTimer;

	void setDir();

	bool NeedsToGoLeft();

	void UpOrDown(bool goingUp);

	void fall(float deltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = AI)
	void setRowAndCol(int row, int col);
	UFUNCTION(BlueprintCallable, Category = AI)
	void SetTargetRowAndCol(int row, int col);
	UFUNCTION(BlueprintImplementableEvent, Category = AI)
		void SettingTarget();
	

	//starts the time line in the eventGraph
	UFUNCTION(BlueprintCallable, Category = movement)
		void Jump();

	UFUNCTION(BlueprintCallable, Category = movement)
		void JumpLerp(float time, FVector direction);
	UFUNCTION(BlueprintCallable, Category = movement)
		void StopFalling();

	UFUNCTION(BlueprintCallable, Category = Spawning)
		void SpawnIn(FVector pos);

	UFUNCTION(BlueprintCallable, Category = Spawning)
		void Despawn();
};
