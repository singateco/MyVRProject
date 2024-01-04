// Fill out your copyright notice in the Description page of Project Settings.


#include "CarControllerComponent.h"

#include "MotionControllerComponent.h"
#include "MyCar.h"
#include "VR_Player.h"
#include "Components/TextRenderComponent.h"

// Sets default values for this component's properties
UCarControllerComponent::UCarControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCarControllerComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	TArray<UInputAction*> Inputs)
{
	EnhancedInputComponent->BindAction(Inputs[3], ETriggerEvent::Started, this, &UCarControllerComponent::GripLeftOn);
	EnhancedInputComponent->BindAction(Inputs[3], ETriggerEvent::Completed, this, &UCarControllerComponent::GripLeftOff);
	EnhancedInputComponent->BindAction(Inputs[7], ETriggerEvent::Started, this, &UCarControllerComponent::GripRightOn);
	EnhancedInputComponent->BindAction(Inputs[7], ETriggerEvent::Completed, this, &UCarControllerComponent::GripRightOff);
}


// Called when the game starts
void UCarControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = GetOwner<AVR_Player>();
}

// 기준 방향 벡터를 이용해서 왼손과 오른손의 각도 차이를 계산해서 반환하는 함수
float UCarControllerComponent::GetControllerAngle(FVector LeftControllerLoc, FVector RightControllerLoc,
	FVector BaseDirection)
{
	FVector HandVector = (RightControllerLoc - LeftControllerLoc).GetSafeNormal();
	FVector BaseVector = BaseDirection.GetSafeNormal();

	float DotResult = FVector::DotProduct(HandVector, BaseVector);
	float Degree = FMath::RadiansToDegrees(FMath::Acos(DotResult));

	if (FVector::DotProduct(Player->GetActorUpVector(), HandVector) > 0)
	{
		Degree *= -1.f;
	}

	return Degree;
}

void UCarControllerComponent::GripLeftOn()
{
	bIsLeftGrip = true;
}

void UCarControllerComponent::GripLeftOff()
{
	bIsLeftGrip = false;
}

void UCarControllerComponent::GripRightOn()
{
	bIsRightGrip = true;
}

void UCarControllerComponent::GripRightOff()
{
	bIsRightGrip = false;
}


// Called every frame
void UCarControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsLeftGrip && bIsRightGrip)
	{
		float Degree = GetControllerAngle(Player->LeftGrip->GetComponentLocation(), Player->RightGrip->GetComponentLocation(), Player->GetActorRightVector());
		Player->LeftLog->SetText(FText::FromString(FString::Printf(TEXT("Degree : %.3f"), Degree)));
		Player->ControlledCar->RotateCar(Degree);
	}
}

