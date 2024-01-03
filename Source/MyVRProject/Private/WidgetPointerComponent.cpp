// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetInteractionComponent.h"

// Sets default values for this component's properties
UWidgetPointerComponent::UWidgetPointerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UWidgetPointerComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	TArray<UInputAction*> Inputs)
{
	EnhancedInputComponent->BindAction(Inputs[6], ETriggerEvent::Started, this, &UWidgetPointerComponent::MouseLeftClick);
	EnhancedInputComponent->BindAction(Inputs[6], ETriggerEvent::Completed, this, &UWidgetPointerComponent::MouseLeftClickReleased);

}


// Called when the game starts
void UWidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = GetOwner<AVR_Player>();
}

void UWidgetPointerComponent::MouseLeftClick(const FInputActionInstance& InputActionInstance)
{
	// 오른쪽 위젯 인터액션 포인터에 오른쪽 트리거 누를시 마우스 클릭
	Player->RightPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void UWidgetPointerComponent::MouseLeftClickReleased(const FInputActionInstance& InputActionInstance)
{
	Player->RightPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}
