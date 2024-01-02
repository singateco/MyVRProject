// Fill out your copyright notice in the Description page of Project Settings.


#include "GazeComponent.h"
#include "VR_Player.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UGazeComponent::UGazeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGazeComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = GetOwner<AVR_Player>();
	BaseSize = Player->GazeMeshComp->GetRelativeScale3D();
}


// Called every frame
void UGazeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 만일 시선 방향에 물체가 있다면 게이즈 포인터의 크기를 증가시킨다 (MaxSize 까지만)
	// 그렇지 않다면 게이즈 포인터의 크기를 감소시킨다 (MinSize 까지만)

	FHitResult OutHits;
	const FVector StartLoc = Player->CameraComponent->GetComponentLocation();
	const FVector EndLoc = StartLoc + Player->CameraComponent->GetForwardVector() * 2500;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);

	const float InterpSpeed = 2.f;

	if (GetWorld()->LineTraceSingleByChannel(OutHits, StartLoc, EndLoc, ECC_Visibility, Params))
	{
		// 물체가 있음
		Player->GazeMeshComp->SetRelativeScale3D(FMath::VInterpTo(Player->GazeMeshComp->GetRelativeScale3D(), BaseSize * MaxSize, DeltaTime, InterpSpeed));
	}
	else
	{
		Player->GazeMeshComp->SetRelativeScale3D(FMath::VInterpTo(Player->GazeMeshComp->GetRelativeScale3D(), BaseSize * MinSize, DeltaTime, InterpSpeed));
	}
	
}