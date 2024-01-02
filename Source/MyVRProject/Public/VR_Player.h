// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "VR_Player.generated.h"

class UMoveComponent;
class UTextRenderComponent;
class UMotionControllerComponent;
class UCameraComponent;

UCLASS()
class MYVRPROJECT_API AVR_Player : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AVR_Player();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 카메라
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UCameraComponent* CameraComponent;

	// 카메라 메시
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UStaticMeshComponent* HMDMesh;

	// 왼쪽 손
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UMotionControllerComponent* LeftGrip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	USkeletalMeshComponent* LeftHandMesh;

	// 오른쪽 손
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UMotionControllerComponent* RightGrip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	USkeletalMeshComponent* RightHandMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UTextRenderComponent* LeftLog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UTextRenderComponent* RightLog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UInputAction* RightThumbStick;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UInputAction* RightIndexTrigger_Bool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UInputAction* RightIndexTrigger_Float;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UInputAction* RightIndexTrigger_Touch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UInputAction* LeftIndexTrigger_Bool;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	TArray<class UInputAction*> Ia_Inputs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UMoveComponent* MoveComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UGrabComponent* GrabComp;

	// 애니메이션 담당 컴포넌트
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UVRHandAnimComponent* HandAnimComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UNiagaraComponent* TeleportFX;

	UPROPERTY()
	class UVRBodyAnimInstance* BodyAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	UStaticMeshComponent* GazeMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MySettings|Components")
	class UGazeComponent* GazeComp;

	APlayerController* PC;

	float RecenterTickTimer {0.f};

	UPROPERTY(EditAnywhere)
	float RecenterHoldAmountSeconds {1.0f};

	bool RecenterTick {false};

private:

	void RightTriggerInput_Bool(const FInputActionValue& Value);
	void RightTriggerInput_Float(const FInputActionValue& Value);
	void RightTriggerInput_Touch(const FInputActionValue& Value);
	void RightThumbStickInput(const FInputActionValue& Value);
	void MoveActionInput(const FInputActionValue& Value);
	void RecenterStart(const FInputActionValue& Value);
	void Recenter(const FInputActionValue& Value);
	void RecenterInputStop(const FInputActionValue& Value);
	void PlayerRotate(const FInputActionValue& Value);

	void BasicTeleport(float SightRange, const FVector& Direction, const FVector& Pivot);
};
