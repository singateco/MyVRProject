// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "MotionControllerComponent.h"
#include "VRDrawFunctionLibrary.h"
#include "VR_Player.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	UE_LOG(LogTemp, Warning, TEXT("Component Begin Play"))
	Player = GetOwner<AVR_Player>();
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	TArray<UInputAction*> InputActions)
{
	// DrawTrajectory를 바로 바인딩 할 수 없으므로 중계함수를 사용한다
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Triggered, this, &UMoveComponent::ShowLine);
	// 트리거에서 손을 놓았을시 순간이동
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Completed, this, &UMoveComponent::Teleport);
}

// 예측선 보이게 하는 함수
void UMoveComponent::ShowLine(const FInputActionValue& Value)
{
	bool bIsPressed = Value.Get<bool>();

	Player->LeftLog->SetText(FText::FromString(FString::Printf(TEXT("%s"), bIsPressed ? *FString("Pressed") : *FString("Released"))));

	DrawDebugLine(GetWorld(), Player->LeftHandMesh->GetComponentLocation(), Player->LeftHandMesh->GetComponentLocation() + Player->LeftHandMesh->GetRightVector() * 5000, FColor::Blue, false, 0, 0, .5f);

	if (nullptr != Player && bIsPressed)
	{
		//DrawTrajectory(Player->LeftHandMesh->GetComponentLocation(), Player->LeftHandMesh->GetForwardVector() * -1 + Player->LeftHandMesh->GetRightVector(), LineSpeed, 50, 0.1f);
		DrawTrajectoryBezier(Player->LeftHandMesh->GetComponentLocation(), Player->LeftHandMesh->GetRightVector(), 50, 5000);
	}
}

// 예측 선을 계산하고 그리는 함수 (중력 방식)
void UMoveComponent::DrawTrajectory(const FVector& StartLoc, const FVector& Direction, const float Speed, const int32 Segment, const float Interval)
{
	// Direction 방향으로 Segment 회만큼 Interval 간격 (초)로 반복해서 이동했을 위치를 계산한다.
	// 계산 결과 값들은 배열에 담아놓는다.

	// 값을 담아놓을 배열.
	TArray<FVector> LinePositions;

	for (int32 i = 0; i < Segment; i++)
	{
		const float ElapsedTime = Interval * i;

		FVector GravityVec = FVector(0, 0, GetWorld()->GetGravityZ());

		// 자유낙하식 1/2gt^2 라고 함 (상업계라 잘 모름)
		FVector NewLocation = StartLoc + Direction * Speed * ElapsedTime + (0.5f * GravityVec * ElapsedTime * ElapsedTime);

		// 뭔가에 부딪혔을시 배열에 그만 추가함
		FHitResult HitResult;
		if (LinePositions.Num() > 0 && GetWorld()->LineTraceSingleByChannel(HitResult, LinePositions[i - 1], NewLocation, ECC_Visibility))
		{
			// 마지막 점을 부딪힌 부분으로 함
			LinePositions.Add(HitResult.ImpactPoint);
			break;
		}

		LinePositions.Add(NewLocation);
	}

	for (int32 i = 0; i < LinePositions.Num() -1; i++)
	{
		DrawDebugLine(GetWorld(), LinePositions[i], LinePositions[i + 1], FColor::Green, false, 0, 0, 2.f);
	}

	// 마지막 위치에 빨강 상자를 표시한다.
	DrawDebugBox(GetWorld(), LinePositions.Last(), FVector(5), FColor::Red, false, 0, 0, 0.5f);

	// 이동할 곳을 저장
	TargetLocation = LinePositions.Last();
}

void UMoveComponent::DrawTrajectoryBezier(const FVector& StartLoc, const FVector& Direction, const int32 Segment, const int32 Length)
{
	FHitResult HitResult;
	FVector EndLoc;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, StartLoc + Direction * Length, ECC_Visibility))
	{
		EndLoc = HitResult.ImpactPoint;
	}

	if (!EndLoc.IsNearlyZero())
	{
		FVector P1 = FMath::Lerp(StartLoc, EndLoc, 0.5);
		P1.Z *= 5;

		DrawDebugPoint(GetWorld(), P1, 20, FColor::Purple);
		
		TArray<FVector> DrawPoints = UVRDrawFunctionLibrary::CalculateBezierCurve(StartLoc, P1, EndLoc, 50);

		for (int i = 0; i < DrawPoints.Num() - 1; i++)
		{
			DrawDebugLine(GetWorld(), DrawPoints[i], DrawPoints[i + 1], FColor::Red, false, 0, 0, 2);
		}
	}
		
}

// 목표 지정으로 순간이동하는 함수
void UMoveComponent::Teleport()
{
	// Black Fade In 효과를 준다.
	Player->GetController<APlayerController>()->PlayerCameraManager->StartCameraFade(0, 1.f, TeleportDelayTime, FLinearColor::Black);

	// TeleportDelayTime 시이 지난후 텔레포트한다.
	if (!TargetLocation.IsNearlyZero())
	{
		FTimerHandle TeleportTimer;

		GetWorld()->GetTimerManager().SetTimer(TeleportTimer, FTimerDelegate::CreateLambda([&]()
			{
				Player->SetActorLocation(TargetLocation + FVector(0, 0, Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
			}), TeleportDelayTime, false);
	}

}
