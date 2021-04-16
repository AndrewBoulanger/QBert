// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QBertGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameWonEvent, float, duration);


/**
 * 
 */
UCLASS()
class QBERT_API AQBertGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	int score = 0;
	
	int lives = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = score, meta = (AllowPrivateAccess = "true"))
	int activeElevators = 2;
	
	int remainingPlatforms = 28;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = gameOver, meta = (AllowPrivateAccess = "true"))
	float songDuration = 1.0;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Ui)
	void updateUI();


	UFUNCTION(BlueprintCallable, Category = Ui)
	int getScore(){return score;}
	UFUNCTION(BlueprintCallable, Category = Ui)
		void raiseScore(int val)
	{
		score += val;
		updateUI();
	}

	UFUNCTION(BlueprintCallable, Category = Ui)
		int getLives() { return lives; }
	UFUNCTION(BlueprintCallable, Category = Ui)
		void loseLife();
	

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, category = gameOver)
	void OnGameOver();
	UFUNCTION(BlueprintImplementableEvent, category = gameOver)
	void OnWin(float duration);

	UPROPERTY(BlueprintAssignable, Category = gameOver)
	FOnGameWonEvent OnGameWon;
	
	UFUNCTION(BlueprintCallable, Category = Ui)
	void reduceElevators()
	{
		activeElevators--;
	}
	UFUNCTION(BlueprintCallable, Category = Ui)
	void reduceRemainingPlatforms();
	
};
