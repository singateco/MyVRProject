// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BezierCurveActor.generated.h"

UCLASS()
class MYVRPROJECT_API ABezierCurveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABezierCurveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USceneComponent* P0;

	UPROPERTY(EditAnywhere)
	USceneComponent* P1;

	UPROPERTY(EditAnywhere)
	USceneComponent* P2;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (UIMin = 0.f, UIMax = 1.f, ClampMin = 0.f, ClampMax = 1.f))
	float T = 0;

	void DrawBezierCurve(FVector Loc0, FVector Loc1, FVector Loc2);
};
