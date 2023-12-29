// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabComponent();

	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> Inputs);

	UPROPERTY()
	class APickUpActor* CurrentlyGrabbedObject;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UHapticFeedbackEffect_Curve* GrabHaptic;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY()
	class AVR_Player* Player;
	UPROPERTY()
	FVector PrevLocation;
	UPROPERTY()
	FVector DeltaLoc;

	UPROPERTY()
	FQuat PrevQuat;
	UPROPERTY()
	FQuat DeltaQuat;


	void GrabObject();
	void ReleaseObject();
};
