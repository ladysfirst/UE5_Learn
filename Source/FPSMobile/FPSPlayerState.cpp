// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerState.h"

AFPSPlayerState::AFPSPlayerState()
{
	// 初始化分数为 0
	PlayerScore = 0;
}

void AFPSPlayerState::IncreaseScore(int32 Amount)
{
	PlayerScore += Amount;
	// 可以在此处添加任何更新 UI 或广播分数变化的逻辑
	UE_LOG(LogTemp, Log, TEXT("Player %s score: %d"), *GetPlayerName(), PlayerScore);
	FString Message = FString::Printf(TEXT("Player: %s, Score: %d"), *GetPlayerName(), PlayerScore);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	}
}


