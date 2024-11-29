// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPSMOBILE_API AFPSPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AFPSPlayerState();
	// 当前玩家的积分
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Score")
	int32 PlayerScore;
	
	// 增加积分的函数
	UFUNCTION(BlueprintCallable, Category = "Score")
	void IncreaseScore(int32 Amount);

	// 获取当前分数
	int32 GetScore() const { return PlayerScore; }
};
