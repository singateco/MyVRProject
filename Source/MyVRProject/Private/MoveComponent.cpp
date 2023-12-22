// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "MotionControllerComponent.h"
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
	// DrawTrajectory�� �ٷ� ���ε� �� �� �����Ƿ� �߰��Լ��� ����Ѵ�
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Triggered, this, &UMoveComponent::ShowLine);
	// Ʈ���ſ��� ���� �������� �����̵�
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Completed, this, &UMoveComponent::Teleport);
}

// ������ ���̰� �ϴ� �Լ�
void UMoveComponent::ShowLine(const FInputActionValue& Value)
{
	bool bIsPressed = Value.Get<bool>();

	Player->LeftLog->SetText(FText::FromString(FString::Printf(TEXT("%s"), bIsPressed ? *FString("Pressed") : *FString("Released"))));

	if (nullptr != Player && bIsPressed)
	{
		DrawTrajectory(Player->LeftHandMesh->GetComponentLocation(), Player->LeftHandMesh->GetForwardVector() * -1 + Player->LeftHandMesh->GetRightVector(), LineSpeed, 50, 0.1f);
			
	}
}

// ���� ���� ����ϰ� �׸��� �Լ� (�߷� ���)
void UMoveComponent::DrawTrajectory(const FVector& StartLoc, const FVector& Direction, const float Speed, const int32 Segment, const float Interval)
{
	// Direction �������� Segment ȸ��ŭ Interval ���� (��)�� �ݺ��ؼ� �̵����� ��ġ�� ����Ѵ�.
	// ��� ��� ������ �迭�� ��Ƴ��´�.

	// ���� ��Ƴ��� �迭.
	TArray<FVector> LinePositions;

	for (int32 i = 0; i < Segment; i++)
	{
		const float ElapsedTime = Interval * i;

		FVector GravityVec = FVector(0, 0, GetWorld()->GetGravityZ());

		// �������Ͻ� 1/2gt^2 ��� �� (������ �� ��)
		FVector NewLocation = StartLoc + Direction * Speed * ElapsedTime + (0.5f * GravityVec * ElapsedTime * ElapsedTime);

		// ������ �ε������� �迭�� �׸� �߰���
		FHitResult HitResult;
		if (LinePositions.Num() > 0 && GetWorld()->LineTraceSingleByChannel(HitResult, LinePositions[i - 1], NewLocation, ECC_Visibility))
		{
			// ������ ���� �ε��� �κ����� ��
			LinePositions.Add(HitResult.ImpactPoint);
			break;
		}

		LinePositions.Add(NewLocation);
	}

	for (int32 i = 0; i < LinePositions.Num() -1; i++)
	{
		DrawDebugLine(GetWorld(), LinePositions[i], LinePositions[i + 1], FColor::Green, false, 0, 0, 2.f);
	}

	// ������ ��ġ�� ���� ���ڸ� ǥ���Ѵ�.
	DrawDebugBox(GetWorld(), LinePositions.Last(), FVector(5), FColor::Red, false, 0, 0, 0.5f);

	// �̵��� ���� ����
	TargetLocation = LinePositions.Last();
}

// ��ǥ �������� �����̵��ϴ� �Լ�
void UMoveComponent::Teleport()
{
	if (!TargetLocation.IsNearlyZero())
	{
		Player->SetActorLocation(TargetLocation + FVector(0, 0, Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	}
}
