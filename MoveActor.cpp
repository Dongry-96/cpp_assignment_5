// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMoveActor::AMoveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartLocation = { 0,0 };
	PositionList.Add(StartLocation);
	bIsEvent = false;
	EventCnt = 0;
}

// Called when the game starts or when spawned
void AMoveActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("StartLocation: (%1.f, %1.f)"), StartLocation.X, StartLocation.Y);

	Move();
}


// 이동할 수치 Struct에 저장 메서드
// 0~1 사이의 난수를 X와 Y 따로 Struct에 저장합니다.
void AMoveActor::Step()
{
	int MinValue = 0;
	int MaxValue = 1;

	StepValue.X = FMath::RandRange(MinValue, MaxValue);
	StepValue.Y = FMath::RandRange(MinValue, MaxValue);

}

// 이동 및 현재 위치 출력, 이벤트 발생여부 출력 메서드
// 1. Step 함수를 사용해서 이동한 좌표를 10회 저장합니다.
// 2. 1번 인덱스부터 순회하며 현재 위치와 전 위치에서 현재 위치로 이동한 거리를 출력합니다.
// 3. CreateEvent 함수를 통해 이벤트 발생여부를 확인한 후, 발생했다면 이벤트를 출력합니다.
// 4. 마지막으로 전체 이동거리와 총 이벤트 발생 횟수를 출력합니다.
void AMoveActor::Move()
{
	for (int i = 0; i < 10; i++)
	{
		Step();
		
		PositionList.Add({ PositionList[i].X + StepValue.X, PositionList[i].Y + StepValue.Y });
	}

	int ListSize = PositionList.Num();
	for (int i = 1; i < ListSize; i++)
	{
		float Distance = GetDistance(PositionList[i - 1], PositionList[i]);
		UE_LOG(LogTemp, Warning, TEXT("Current Location: (%1.f, %1.f), MoveDistance: %.1f"), PositionList[i].X, PositionList[i].Y, Distance);

		bIsEvent = CreateEvent();
		if (bIsEvent)
		{
			UE_LOG(LogTemp, Error, TEXT("Event was Triggered!"));
			bIsEvent = false;
			EventCnt++;
		}
	}

	float TotalMovedDistance = GetDistance(StartLocation, PositionList.Last());
	UE_LOG(LogTemp, Display, TEXT("Total Moved Distance: %.1f, Event Count: %d"), TotalMovedDistance, EventCnt);
}

// 두 위치 Vector의 거리를 계산하는 메서드
// 유클리드 거리 공식을 통해 두 Vector의 거리를 계산한 뒤 반환합니다.
float AMoveActor::GetDistance(const FVector2D& FirstLocation, const FVector2D& SecondLocation)
{
	float DeltaX = SecondLocation.X - FirstLocation.X;
	float DeltaY = SecondLocation.Y - FirstLocation.Y;

	return FMath::Sqrt((DeltaX * DeltaX) + (DeltaY * DeltaY));
}

// 50퍼센트 확률로 Event 발생 여부 반환 메서드
bool AMoveActor::CreateEvent()
{
	float Probability = FMath::FRand();
	if (Probability >= 0.5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

