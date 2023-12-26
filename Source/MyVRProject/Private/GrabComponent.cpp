// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"

#include "MotionControllerComponent.h"
#include "PickUpActor.h"
#include "VR_Player.h"
#include "Components/TextRenderComponent.h"

// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	TArray<UInputAction*> Inputs)
{
	EnhancedInputComponent->BindAction(Inputs[1], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = GetOwner<AVR_Player>();
}


// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrabComponent::GrabObject()
{
	//Player->RightLog->SetText(FText::FromString(FString("Try Grabbed")));

	UWorld* World = GetWorld();

#pragma region 1. 라인 트레이스를 이용한 경우
	if (World)
	{
		FHitResult HitResult;
		FVector StartLoc = Player->RightGrip->GetComponentLocation();
		FVector EndLoc = StartLoc + Player->RightGrip->GetRightVector() * 30;

		if (World->LineTraceSingleByProfile(HitResult, StartLoc, EndLoc, FName("PickUpPreset")))
		{
			if (APickUpActor* PickedObject = Cast<APickUpActor>(HitResult.GetActor()))
			{
				PickedObject->Grabbed(Player->RightHandMesh);
			}
		}
	}

#pragma endregion

	// 2. 스피어 트레이스를 이용할 경우

	// 3. 오버랩 스피어를 이용할 경우

}

