// Copyright Epic Games, Inc. All Rights Reserved.


#include "QBertGameModeBase.h"

void AQBertGameModeBase::loseLife()
{
	lives--;
	updateUI();
	if(lives < 0)
	{
		OnGameOver();
	}

}

void AQBertGameModeBase::reduceRemainingPlatforms()
{
	remainingPlatforms--;
	raiseScore(25);
	if(remainingPlatforms <=0)
	{
		OnGameWon.AddDynamic(this, &AQBertGameModeBase::OnWin);
		OnGameWon.Broadcast(songDuration);
	}
}
