// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor.generated.h"

UCLASS()
class BASIS_API AMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	struct FStepValue
	{
		int X;
		int Y;
	};

	FStepValue StepValue;
	FVector2D StartLocation;
	TArray<FVector2D> PositionList;
	int32 EventCnt;
	bool bIsEvent;

	void Step();
	void Move();
	float GetDistance(const FVector2D& FirstLocation, const FVector2D& SecondLocation);
	bool CreateEvent();
};
