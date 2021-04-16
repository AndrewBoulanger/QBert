// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM() 
enum direction
{
	UP_LEFT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT
};

#include "QBertGameModeBase.h"
#include "Components/TimelineComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "playerPawn.generated.h"


UCLASS()
class QBERT_API AplayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AplayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	TEnumAsByte<direction> dir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AQBertGameModeBase* gameMode = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	int m_row;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	int m_column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	UTimelineComponent* Timeline;

	FVector m_initialPos;

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
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUpLeft();
	void MoveDownLeft();
	void MoveUpRight();
	void MoveDownRight();

	void fall(float deltaTime);

	float timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool b_isJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float fallRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool isFalling;
	float gravity;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//starts the time line in the eventGraph
	UFUNCTION(BlueprintCallable, Category = movement)
	void Jump();

	UFUNCTION(BlueprintCallable, Category = movement)
		void JumpLerp(float time, FVector direction);


	UFUNCTION(BlueprintCallable, Category = location)
		void resetRowAndColumn();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Ui)
		void resetEnemies();

	UFUNCTION(BlueprintImplementableEvent, Category = location)
		void OnDelay();
};
