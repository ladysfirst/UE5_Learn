// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSMobileGameMode.h"
#include "FPSMobileCharacter.h"
#include "FPSPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AFPSMobileGameMode::AFPSMobileGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	//初始化游戏时间
	CountdownTime = 20;
}

void AFPSMobileGameMode::IncreasePlayerScore(APlayerController* PlayerController, int32 Amount)
{
	if (PlayerController)
	{
		AFPSPlayerState* PlayerState = Cast<AFPSPlayerState>(PlayerController->PlayerState);
		if (PlayerState)
		{
			PlayerState->IncreaseScore(Amount);
		}
	}
}

void AFPSMobileGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 设置定时器，每秒调用一次 UpdateCountdown
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AFPSMobileGameMode::UpdateCountdown, 1.0f, true);
}

void AFPSMobileGameMode::UpdateCountdown()
{
	if (CountdownTime > 0)
	{
		OnGameTimeEvent.Broadcast();
		CountdownTime--;
		UE_LOG(LogTemp, Warning, TEXT("Countdown: %d"), CountdownTime);
	}
	else
	{
		// 清除定时器
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		OnGameTimeEvent.Broadcast();
		// 游戏结束逻辑，例如加载结算画面
		UE_LOG(LogTemp, Warning, TEXT("Game Over!"));

		// 切换到结算UI
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		// UGameplayStatics::OpenLevel(this, FName("GameOverLevel"));
	}
}

