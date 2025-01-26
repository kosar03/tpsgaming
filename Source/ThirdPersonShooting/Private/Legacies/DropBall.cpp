// Fill out your copyright notice in the Description page of Project Settings.


#include "Legacies/DropBall.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADropBall::ADropBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);

}

// Called when the game starts or when spawned
void ADropBall::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ADropBall::BeginOverlapFunc);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ADropBall::EndOverlapFunc);


}

void ADropBall::BeginOverlapFunc(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	BallEffect(OtherActor);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), BallSound, GetActorLocation());
	Destroy();
}

void ADropBall::EndOverlapFunc(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{

}

void ADropBall::BallEffect(AActor* EffectActor)
{

}

// Called every frame
void ADropBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//获取Actor当前位置及旋转
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	//获取自创建以来的游戏时间
	float RunningTime = GetGameTimeSinceCreation();
	//计算高度增量
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;
	//将新的旋转Yaw以及高度设置给Actor
	SetActorLocationAndRotation(NewLocation, NewRotation);

}

