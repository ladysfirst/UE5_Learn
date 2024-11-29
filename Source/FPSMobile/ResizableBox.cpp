// Fill out your copyright notice in the Description page of Project Settings.


#include "ResizableBox.h"

#include "FPSConfigData.h"
#include "FPSPlayerState.h"


// Sets default values
AResizableBox::AResizableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建静态网格体组件
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	
	// 设置碰撞响应
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));

	// 绑定碰撞事件
	StaticMesh->OnComponentHit.AddDynamic(this, &AResizableBox::OnMeshHit);

	//初始化为未命中
	bIsHitted = false;

	static ConstructorHelpers::FObjectFinder<UFPSConfigData> DataAssetFinder(TEXT("/Game/FirstPerson/Config/DA_FPSConfig"));
	if (DataAssetFinder.Succeeded())
	{
		FPSConfig = DataAssetFinder.Object;
	}
}

// Called when the game starts or when spawned
void AResizableBox::BeginPlay()
{
	Super::BeginPlay();
	// 判断是否为特殊物体
	float RandomNumber = FMath::FRand();
	if(RandomNumber >= 0.6)
	{
		if (MaterialAsset)
		{
			StaticMesh->SetMaterial(0, MaterialAsset);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to find the material instance at the specified path!"));
		}
		bIsSpecial = true;
	}
}

// Called every frame
void AResizableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AResizableBox::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
								 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 判断是否与子弹碰撞
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Bullet")))
	{
		// 获取玩家控制器并增加分数
		APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			AFPSPlayerState* PlayerState = Cast<AFPSPlayerState>(PlayerController->PlayerState);
			if (PlayerState)
			{
				if(FPSConfig)
				{
					if(!bIsSpecial)
					{
						PlayerState->IncreaseScore(FPSConfig->FPSScore);  // 每次碰撞增加 FPSScore分
					}
					else
					{
						PlayerState->IncreaseScore(FPSConfig->FPSScore_Special);  // 每次碰撞增加 FPSScore分
					}
				}
			}
			OnScoreEvent.Broadcast();
		}
		if(!bIsHitted)
		{
			// 缩小网格体
			FVector CurrentScale = GetActorScale3D();
			if(FPSConfig)
			{
				float Scale = FPSConfig->FPSScale;
				SetActorScale3D(CurrentScale * Scale); // 缩放Scale的倍数
				bIsHitted = true;
			}
		}
		else
		{
			Destroy();
		}
	}
}