// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> InputActions);

	class AVR_Player* Player;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float LineSpeed = 500;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float TeleportDelayTime = 1.f;

private:
	void ShowLine(const FInputActionValue& Value);
	void DrawTrajectory(const FVector& StartLoc, const FVector& Direction, const float Speed, const int32 Segment, const float Interval);
	void Teleport();

	FVector TargetLocation;
};
