// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSConfigData.h"
#include "GameFramework/Actor.h"
#include "ResizableBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreEventDelegate);
UCLASS()
class FPSMOBILE_API AResizableBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResizableBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "DataAsset")
	UFPSConfigData* FPSConfig;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* MaterialAsset;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnScoreEventDelegate OnScoreEvent;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsHitted;

	UPROPERTY(BlueprintReadWrite)
	bool bIsSpecial = false;
	
	UFUNCTION(BlueprintCallable)
	void OnMeshHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, 
					UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
