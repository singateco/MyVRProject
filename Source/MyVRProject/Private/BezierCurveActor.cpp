// Fill out your copyright notice in the Description page of Project Settings.


#include "BezierCurveActor.h"

#include "VRDrawFunctionLibrary.h"

// Sets default values
ABezierCurveActor::ABezierCurveActor()
	: Root(CreateDefaultSubobject<USceneComponent>(TEXT("Root"))),
	  P0(CreateDefaultSubobject<USceneComponent>(TEXT("P0"))),
	  P1(CreateDefaultSubobject<USceneComponent>(TEXT("P1"))),
	  P2(CreateDefaultSubobject<USceneComponent>(TEXT("P2")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(Root);
	P0->SetupAttachment(RootComponent);
	P1->SetupAttachment(RootComponent);
	P2->SetupAttachment(RootComponent);

	P0->SetRelativeLocation(FVector(-20, 0, 20));
	P1->SetRelativeLocation(FVector(0, 0, 50));
	P2->SetRelativeLocation(FVector(20, 0, 20));
}

// Called when the game starts or when spawned
void ABezierCurveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABezierCurveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawBezierCurve(P0->GetComponentLocation(), P1->GetComponentLocation(), P2->GetComponentLocation());

}

void ABezierCurveActor::DrawBezierCurve(FVector Loc0, FVector Loc1, FVector Loc2)
{

	TArray<FVector> LinePositions = UVRDrawFunctionLibrary::CalculateBezierCurve(Loc0, Loc1, Loc2, 50);

	const UWorld* World = GetWorld();
	DrawDebugLine(World, Loc0, Loc1, FColor::Black, false, 0, 0, 2.f);
	DrawDebugLine(World, Loc1, Loc2, FColor::Black, false, 0, 0, 2.f);
	//DrawDebugPoint(World, M0, 20, FColor::White);
	//DrawDebugPoint(World, M1, 20, FColor::White);
	//DrawDebugPoint(World, B, 35, FColor::Purple, false, 2);

	if (LinePositions.Num() > 0)
	{
		for (int32 i = 0; i < LinePositions.Num() - 1; i++)
		{
			DrawDebugLine(World, LinePositions[i], LinePositions[i + 1], FColor::Magenta, false, 0, 0, 1);
		}
	}
}

