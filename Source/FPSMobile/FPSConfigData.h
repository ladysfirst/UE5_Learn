// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FPSConfigData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class FPSMOBILE_API UFPSConfigData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	//单次得分设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 FPSScore = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 FPSScore_Special = 0;
	//可变大小设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale")
	float FPSScale = 1;
};
