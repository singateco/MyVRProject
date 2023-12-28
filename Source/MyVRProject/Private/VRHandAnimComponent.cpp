// Fill out your copyright notice in the Description page of Project Settings.


#include "VRHandAnimComponent.h"

#include "EnhancedInputComponent.h"
#include "VRHandAnimInstance.h"
#include "VR_Player.h"

// Sets default values for this component's properties
UVRHandAnimComponent::UVRHandAnimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVRHandAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Player = GetOwner<AVR_Player>();

	if (nullptr != Player)
	{
		HandAnim_Left = Cast<UVRHandAnimInstance>(Player->LeftHandMesh->GetAnimInstance());
		// 왼손은 Mirror 변수를 바꿔준다
		if (HandAnim_Left)
		{
			HandAnim_Left->bMirror_cpp = true;
		}

		HandAnim_Right = Cast<UVRHandAnimInstance>(Player->RightHandMesh->GetAnimInstance());
		if (HandAnim_Right)
		{
			HandAnim_Right->bMirror_cpp = false;
		}
	}
	
}


// Called every frame
void UVRHandAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVRHandAnimComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	TArray<UInputAction*> InputActions)
{
	// 왼쪽 검지 트리거 누르는 값
	EnhancedInputComponent->BindAction(InputActions[2], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerValue_Left);
	EnhancedInputComponent->BindAction(InputActions[2], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerValue_Left);

	// 왼쪽 그립 트리거 누르는 값
	EnhancedInputComponent->BindAction(InputActions[3], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputGripValue_Left);
	EnhancedInputComponent->BindAction(InputActions[3], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputGripValue_Left);

	// 왼쪽 엄지 터치
	EnhancedInputComponent->BindAction(InputActions[4], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputThumbStickTouch_Left);
	EnhancedInputComponent->BindAction(InputActions[4], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputThumbStickTouch_Left);


	// 왼쪽 검지 트리거 터치
	EnhancedInputComponent->BindAction(InputActions[5], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Left);
	EnhancedInputComponent->BindAction(InputActions[5], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Left);

	// 오른쪽 검지 트리거 누르는 값
	EnhancedInputComponent->BindAction(InputActions[6], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerValue_Right);
	EnhancedInputComponent->BindAction(InputActions[6], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerValue_Right);

	// 오른쪽 그립 트리거 누르는 값
	EnhancedInputComponent->BindAction(InputActions[7], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputGripValue_Right);
	EnhancedInputComponent->BindAction(InputActions[7], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputGripValue_Right);

	// 오른쪽 엄지 터치
	EnhancedInputComponent->BindAction(InputActions[8], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputThumbStickTouch_Right);
	EnhancedInputComponent->BindAction(InputActions[8], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputThumbStickTouch_Right);

	// 오른쪽 검지 트리거 터치
	EnhancedInputComponent->BindAction(InputActions[9], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Right);
	EnhancedInputComponent->BindAction(InputActions[9], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Right);
}

void UVRHandAnimComponent::InputIndexTriggerValue_Left(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Left)
	{
		HandAnim_Left->PoseAlphaIndexCurl_cpp = Value.Get<float>();
	}
}

void UVRHandAnimComponent::InputGripValue_Left(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Left)
	{
		HandAnim_Left->PoseAlphaGrasp_cpp = Value.Get<float>();
	}
}

void UVRHandAnimComponent::InputIndexTriggerTouch_Left(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Left)
	{
		HandAnim_Left->PoseAlphaPoint_cpp = Value.Get<bool>() == true ? 0 : 1.0f;
	}
}

void UVRHandAnimComponent::InputThumbStickTouch_Left(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Left)
	{
		HandAnim_Left->PoseAlphaThumbUp_cpp = Value.Get<bool>() == true ? 0 : 1.0f;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("%s"), Value.Get<bool>() ? *FString(TEXT("True")) : *FString(TEXT("False"))));
	}
}

void UVRHandAnimComponent::InputIndexTriggerValue_Right(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Right)
	{
		HandAnim_Right->PoseAlphaIndexCurl_cpp = Value.Get<float>();
	}
}

void UVRHandAnimComponent::InputGripValue_Right(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Right)
	{
		HandAnim_Right->PoseAlphaGrasp_cpp = Value.Get<float>();
	}
}

void UVRHandAnimComponent::InputIndexTriggerTouch_Right(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Right)
	{
		HandAnim_Right->PoseAlphaPoint_cpp = Value.Get<bool>() == true ? 0 : 1.0f;
	}
}

void UVRHandAnimComponent::InputThumbStickTouch_Right(const FInputActionValue& Value)
{
	if (nullptr != HandAnim_Right)
	{
		HandAnim_Right->PoseAlphaThumbUp_cpp = Value.Get<bool>() == true ? 0 : 1.0f;
	}
}

