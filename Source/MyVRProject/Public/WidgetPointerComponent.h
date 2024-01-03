// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "WidgetPointerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UWidgetPointerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWidgetPointerComponent();

	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> Inputs);
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class AVR_Player* Player;

	void MouseLeftClick(const FInputActionInstance& InputActionInstance);
	void MouseLeftClickReleased(const FInputActionInstance& InputActionInstance);
};
