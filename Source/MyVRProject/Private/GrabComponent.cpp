// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"

#include "MotionControllerComponent.h"
#include "PickUpActor.h"
#include "VR_Player.h"
#include "Components/TextRenderComponent.h"
#include "Haptics/HapticFeedbackEffect_Curve.h"

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
	EnhancedInputComponent->BindAction(Inputs[1], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);
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

	// 뭔가 잡고 있을시 위치 & 회전값 저장해놓음 / 저번 프레임값과 비교하여 델타변수에 저장
	if (nullptr != CurrentlyGrabbedObject)
	{
		DeltaLoc = Player->RightGrip->GetComponentLocation() - PrevLocation;
		PrevLocation = Player->RightGrip->GetComponentLocation();

		DeltaQuat = Player->RightGrip->GetComponentQuat() * PrevQuat.Inverse();
		// DeltaQuat = Player->RightGrip->GetComponentQuat() - PrevQuat.Inverse();
		PrevQuat = Player->RightGrip->GetComponentQuat();
	}
}

void UGrabComponent::GrabObject()
{
	//Player->RightLog->SetText(FText::FromString(FString("Try Grabbed")));

	// 무언가 잡고 있을시 탈출
	if (nullptr != CurrentlyGrabbedObject)
	{
		return;
	}


	UWorld* World = GetWorld();

#pragma region 1. 라인 트레이스를 이용한 경우
	/*
	if (World)
	{
		FHitResult HitResult;
		FVector StartLoc = Player->RightGrip->GetComponentLocation();
		FVector EndLoc = StartLoc + Player->RightGrip->GetRightVector() * 30;

		if (World->LineTraceSingleByProfile(HitResult, StartLoc, EndLoc, FName("PickUpPreset")))
		{
			CurrentlyGrabbedObject = Cast<APickUpActor>(HitResult.GetActor());
			if (nullptr != CurrentlyGrabbedObject)
			{
				CurrentlyGrabbedObject->Grabbed(Player->RightHandMesh, EAttachmentRule::SnapToTarget);
			}
		}
	}
	*/

#pragma endregion

	// 2. 스피어 트레이스를 이용할 경우

#pragma region 3. 오버랩 스피어를 이용할 경우

	TArray<FOverlapResult> OverlapResults;

	constexpr float SphereRadius = 25.f;

	// 2번째 파라미터: 오버랩을 사용할 중앙 위치 (배열 순서 결정)
	// 3번째 : 오버랩 회전
	// 4번째 : 감지할 프로필
	// 5번째 : 감지할 도형 만들기
	if (World->OverlapMultiByProfile(OverlapResults, Player->RightGrip->GetComponentLocation(), Player->RightGrip->GetComponentQuat(), FName("PickUpPreset"), FCollisionShape::MakeSphere(SphereRadius)))
	{
		float MinDistance = SphereRadius;
		int32 Idx = 0;

		// 감지된 액터마다 이름을 받아 출력
		//FString ObjectsString;

		for (int32 i = 0; i < OverlapResults.Num(); i++)
		{
			const FOverlapResult Result = OverlapResults[i];

			if (Result.GetActor()->IsA<APickUpActor>())
			{
				//ObjectsString += (Result.GetActor()->GetActorNameOrLabel() + "\r\n");
				// 손에 잡기

				// 거리가 최소값인 액터 구하기
				const float Dist = FVector::Dist(Player->RightGrip->GetComponentLocation(), Result.GetActor()->GetActorLocation());

				if (Dist < MinDistance)
				{
					MinDistance = Dist;
					Idx = i;
				}
			}
		}

		// 가장 거리값이 작은 액터 잡기

		CurrentlyGrabbedObject = Cast<APickUpActor>(OverlapResults[Idx].GetActor());

		if (nullptr != CurrentlyGrabbedObject)
		{
			CurrentlyGrabbedObject->Grabbed(Player->RightHandMesh, EAttachmentRule::SnapToTarget);

			PrevLocation = Player->RightGrip->GetComponentLocation();
			PrevQuat = Player->RightGrip->GetComponentQuat();

			// 진동 효과를 준다.
			if (nullptr != Player->PC && nullptr != GrabHaptic)
			{
				Player->PC->PlayHapticEffect(GrabHaptic, EControllerHand::Right, 1, false);
			}

		}
		
		//Player->RightLog->SetText(FText::FromString(ObjectsString));
	}
	else
	{
		// 감지된 오브젝트가 없을시 출력
		Player->RightLog->SetText(FText::FromString(TEXT("Not Sensing...")));
	}

	// 디버깅용 스피어 그리기
	//DrawDebugSphere(World, Player->RightGrip->GetComponentLocation(), SphereRadius, 30, FColor::Green, false, 1, 0, 1.f);

#pragma endregion

}

void UGrabComponent::ReleaseObject()
{
	if (nullptr == CurrentlyGrabbedObject)
	{
		return;
	}

	CurrentlyGrabbedObject->Released(DeltaLoc, DeltaQuat);
	CurrentlyGrabbedObject = nullptr;
}

