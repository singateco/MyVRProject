// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VRHandAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UVRHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= MySettings)
	float PoseAlphaGrasp_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	float PoseAlphaIndexCurl_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	float PoseAlphaPoint_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	float PoseAlphaThumbUp_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	float CurrentPoseAlphaThumbUp_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	float CurrentPoseAlphaPoint_cpp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	bool bMirror_cpp = false;

};
