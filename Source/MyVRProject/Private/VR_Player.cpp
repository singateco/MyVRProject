// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"

#include "CarControllerComponent.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/TextRenderComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GazeComponent.h"
#include "GrabComponent.h"
#include "MoveComponent.h"
#include "MyCar.h"
#include "NiagaraComponent.h"
#include "VRBodyAnimInstance.h"
#include "VRHandAnimComponent.h"
#include "WidgetPointerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVR_Player::AVR_Player()
	:
	CameraComponent(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"))),
	HMDMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"))),
	LeftGrip(CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Grip"))),
	LeftHandMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"))),
	LeftPointer(CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left Widget Pointer"))),
	RightGrip(CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Grip"))),
	RightHandMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"))),
	RightPointer(CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"))),
	LeftLog(CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"))),
	RightLog(CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"))),
	MoveComp(CreateDefaultSubobject<UMoveComponent>(TEXT("Move Component"))),
	GrabComp(CreateDefaultSubobject<UGrabComponent>(TEXT("Grab Component"))),
	HandAnimComp(CreateDefaultSubobject<UVRHandAnimComponent>(TEXT("VR Hand Anim Component"))),
	TeleportFX(CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport FX"))),
	GazeMeshComp(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gaze Mesh"))),
	GazeComp(CreateDefaultSubobject<UGazeComponent>(TEXT("Gaze Component"))),
	WidgetPointerComp(CreateDefaultSubobject<UWidgetPointerComponent>(TEXT("Widget Pointer Component"))),
	CarControllerComponent(CreateDefaultSubobject<UCarControllerComponent>(TEXT("Car Controller Component")))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent->SetupAttachment(RootComponent);
	HMDMesh->SetupAttachment(CameraComponent);
	GazeMeshComp->SetupAttachment(CameraComponent);

	GazeMeshComp->SetRelativeLocation(FVector(100, 0, 0));
	GazeMeshComp->SetRelativeRotation(FRotator(0, 180, -90));
	GazeMeshComp->SetRelativeScale3D(FVector(0.1f));
	GazeMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftGrip->SetupAttachment(RootComponent);
	LeftHandMesh->SetupAttachment(LeftGrip);
	LeftPointer->SetupAttachment(LeftHandMesh);

	LeftGrip->SetRelativeLocation(FVector(50, -30, -10));
	LeftHandMesh->SetRelativeRotation(FRotator(90, -180, -10));
	LeftGrip->SetTrackingMotionSource(FName("Left"));

	RightGrip->SetupAttachment(RootComponent);
	RightHandMesh->SetupAttachment(RightGrip);
	RightPointer->SetupAttachment(RightHandMesh);

	RightGrip->SetRelativeLocation(FVector(50, 30, -10));
	RightHandMesh->SetRelativeRotation(FRotator(90, 0, 10));
	RightGrip->SetTrackingMotionSource(FName("Right"));

	LeftLog->SetupAttachment(LeftHandMesh);
	LeftLog->SetRelativeLocation(FVector(15, 20, 0));
	LeftLog->SetRelativeRotation(FRotator(270, 630, 0));
	LeftLog->SetHorizontalAlignment(EHTA_Center);
	LeftLog->SetVerticalAlignment(EVRTA_TextCenter);
	LeftLog->SetWorldSize(16);
	LeftLog->SetTextRenderColor(FColor(255, 0, 255));

	RightLog->SetupAttachment(RightHandMesh);
	RightLog->SetRelativeLocation(FVector(-15, 20, 0));
	RightLog->SetRelativeRotation(FRotator(90, -80, 0));
	RightLog->SetHorizontalAlignment(EHTA_Center);
	RightLog->SetVerticalAlignment(EVRTA_TextCenter);
	RightLog->SetWorldSize(16);
	RightLog->SetTextRenderColor(FColor(255, 0, 255));

	TeleportFX->SetupAttachment(LeftGrip);
}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();

	FName TraceTag = TEXT("TraceDebug");

	// 헤드 마운트 디스플레이 장비의 기준 위치를 스테이지로 설정한다.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	PC = GetWorld()->GetFirstPlayerController();

	if (nullptr != PC)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (Subsys)
		{
			Subsys->AddMappingContext(MappingContext, 0);
		}
	}

	BodyAnim = Cast<UVRBodyAnimInstance>(GetMesh()->GetAnimInstance());

	ControlledCar = Cast<AMyCar>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyCar::StaticClass()));
}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/**
	FVector StartLoc = RightGrip->GetComponentTransform().GetLocation();
	FVector UpVector = GetTransform().TransformVector(RightHandMesh->GetForwardVector());
	FVector EndLoc = RightGrip->GetComponentTransform().GetLocation() + UpVector * 10000;

	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Blue, false, 1, 0, 1);
	**/

	if (BodyAnim != nullptr)
	{
		BodyAnim->LeftHandLocation = LeftGrip->GetComponentLocation();
		BodyAnim->LeftHandRotation = LeftGrip->GetComponentRotation();

		BodyAnim->RightHandLocation = RightGrip->GetComponentLocation();
		BodyAnim->RightHandRotation = RightGrip->GetComponentRotation();

		BodyAnim->HeadLocation = CameraComponent->GetComponentLocation();
		BodyAnim->HeadRotation = CameraComponent->GetComponentRotation();
	}

	if (RecenterTick)
	{
		RecenterTickTimer += DeltaTime;
	}

	if (ControlledCar)
	{
		ControlledCar->RotateCar(1);
	}

}

// Called to bind functionality to input
void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// EnhancedInputComponent->BindAction(RightIndexTrigger_Bool, ETriggerEvent::Started, this, &AVR_Player::RightTriggerInput_Bool);
		// EnhancedInputComponent->BindAction(RightIndexTrigger_Bool, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Bool);
		// //EnhancedInputComponent->BindAction(RightIndexTrigger_Float, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Float);
		// //EnhancedInputComponent->BindAction(RightIndexTrigger_Float, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Float);
		// EnhancedInputComponent->BindAction(RightIndexTrigger_Touch, ETriggerEvent::Started, this, &AVR_Player::RightTriggerInput_Touch);
		// EnhancedInputComponent->BindAction(RightIndexTrigger_Touch, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Touch);
		//
		// EnhancedInputComponent->BindAction(RightThumbStick, ETriggerEvent::Triggered, this, &AVR_Player::RightThumbStickInput);
		// EnhancedInputComponent->BindAction(RightThumbStick, ETriggerEvent::Completed, this, &AVR_Player::RightThumbStickInput);
		// EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AVR_Player::MoveActionInput);

		EnhancedInputComponent->BindAction(Ia_Inputs[11], ETriggerEvent::Triggered, this, &AVR_Player::PlayerRotate);
		
		// A버튼을 누를때 뷰 재정렬
		EnhancedInputComponent->BindAction(Ia_Inputs[10], ETriggerEvent::Started, this, &AVR_Player::RecenterStart);
		EnhancedInputComponent->BindAction(Ia_Inputs[10], ETriggerEvent::Triggered, this, &AVR_Player::Recenter);
		EnhancedInputComponent->BindAction(Ia_Inputs[10], ETriggerEvent::Completed, this, &AVR_Player::RecenterInputStop);
		EnhancedInputComponent->BindAction(Ia_Inputs[10], ETriggerEvent::Canceled, this, &AVR_Player::RecenterInputStop);

		// 컴포넌트에 입력 이벤트 넘겨주기
		MoveComp->SetupPlayerInputComponent(EnhancedInputComponent, Ia_Inputs);
		GrabComp->SetupPlayerInputComponent(EnhancedInputComponent, Ia_Inputs);
		HandAnimComp->SetupPlayerInputComponent(EnhancedInputComponent, Ia_Inputs);
		WidgetPointerComp->SetupPlayerInputComponent(EnhancedInputComponent, Ia_Inputs);
		CarControllerComponent->SetupPlayerInputComponent(EnhancedInputComponent, Ia_Inputs);
	}
}

void AVR_Player::RightTriggerInput_Bool(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		RightLog->SetText(FText::FromString(TEXT("Right Trigger Pressed")));
		BasicTeleport(3000, RightHandMesh->GetRightVector().GetSafeNormal(), RightGrip->GetComponentLocation());
	}
	else
	{
		RightLog->SetText(FText::FromString(TEXT("Right Trigger Released")));
	}
	
}

void AVR_Player::RightTriggerInput_Float(const FInputActionValue& Value)
{
	RightLog->SetText(FText::FromString(FString::Printf(TEXT("Right Triggered : %.2f"), Value.Get<float>())));
}

void AVR_Player::RightTriggerInput_Touch(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		RightLog->SetText(FText::FromString(TEXT("Right Trigger Touched")));
	}
	else
	{
		RightLog->SetText(FText::FromString(TEXT("Right Trigger Untouched")));
	}
}

void AVR_Player::RightThumbStickInput(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerYawInput(InputValue.X);

	RightLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), InputValue.X, InputValue.Y)));
}

void AVR_Player::MoveActionInput(const FInputActionValue& Value)
{

	const FVector2D InputValue = Value.Get<FVector2D>();

	const FVector Dir = FVector(InputValue.X, InputValue.Y, 0);

	
	//const FVector ModifiedDir = GetTransform().TransformVector(Dir);
	const FVector WorldDir = FTransform(GetControlRotation()).TransformVector(Dir);

	LeftLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), Dir.X, Dir.Y)));

	AddMovementInput(WorldDir);
}

void AVR_Player::RecenterStart(const FInputActionValue& Value)
{
	RecenterTick = true;
}

void AVR_Player::Recenter(const FInputActionValue& Value)
{
	// 플레이어 시점 재정렬
	if (RecenterTickTimer >= RecenterHoldAmountSeconds)
	{
		UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(0, EOrientPositionSelector::OrientationAndPosition);
		RecenterTickTimer = 0.f;
	}
}

void AVR_Player::RecenterInputStop(const FInputActionValue& Value)
{
	RecenterTick = false;
	RecenterTickTimer = 0.f;
}

void AVR_Player::PlayerRotate(const FInputActionValue& Value)
{
	float InputDir = Value.Get<float>();

	AddControllerYawInput(InputDir);
}

void AVR_Player::BasicTeleport(const float SightRange, const FVector& Direction, const FVector& Pivot)
{
	FHitResult HitResult;
	FVector EndLoc = Pivot + Direction * SightRange;

	DrawDebugLine(GetWorld(), Pivot, EndLoc, FColor::Blue, false, 0.5, 0, 0.75);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Pivot, EndLoc, ECC_Visibility))
	{
		SetActorLocation(HitResult.ImpactPoint + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	}
	
}

