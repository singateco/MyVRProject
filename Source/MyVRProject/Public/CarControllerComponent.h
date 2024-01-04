// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CarControllerComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYVRPROJECT_API UCarControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCarControllerComponent();
	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> Inputs);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class AVR_Player* Player;

	bool bIsLeftGrip{ false };
	bool bIsRightGrip{ false };

	float GetControllerAngle(FVector LeftControllerLoc, FVector RightControllerLoc, FVector BaseDirection);

	void GripLeftOn();
	void GripLeftOff();

	void GripRightOn();
	void GripRightOff();
};
