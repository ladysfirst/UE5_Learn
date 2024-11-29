// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSMobileGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameTimeEventDelegate);
UCLASS(minimalapi)
class AFPSMobileGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSMobileGameMode();
	void IncreasePlayerScore(APlayerController* PlayerController, int32 Amount);

	// 倒计时变量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
	int32 CountdownTime;

	// 倒计时更新函数
	UFUNCTION()
	void UpdateCountdown();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGameTimeEventDelegate OnGameTimeEvent;

protected:
	// 开始游戏时调用
	virtual void BeginPlay() override;

private:
	// 定时器句柄
	FTimerHandle CountdownTimerHandle;
	// 当前显示的Widget实例
};



