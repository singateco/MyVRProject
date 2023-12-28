// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "VRHandAnimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UVRHandAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRHandAnimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> InputActions);

private:
	class AVR_Player* Player;
	class UVRHandAnimInstance* HandAnim_Left;
	UVRHandAnimInstance* HandAnim_Right;

	void InputIndexTriggerValue_Left(const FInputActionValue& Value);
	void InputGripValue_Left(const FInputActionValue& Value);
	void InputIndexTriggerTouch_Left(const FInputActionValue& Value);
	void InputThumbStickTouch_Left(const FInputActionValue& Value);

	void InputIndexTriggerValue_Right(const FInputActionValue& Value);
	void InputGripValue_Right(const FInputActionValue& Value);
	void InputIndexTriggerTouch_Right(const FInputActionValue& Value);
	void InputThumbStickTouch_Right(const FInputActionValue& Value);
};
