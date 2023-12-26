// Fill out your copyright notice in the Description page of Project Settings.


#include "VRDrawFunctionLibrary.h"

TArray<FVector> UVRDrawFunctionLibrary::CalculateBezierCurve(const FVector& P0, const FVector& P1, const FVector& P2,
                                                             const int32 Segment)
{
	TArray<FVector> LinePositions;

	const float Interval = 1.0 / static_cast<float>(Segment);

	for (float i = 0; i < 1.0f; i += Interval)
	{
		FVector M0 = FMath::Lerp(P0, P1, i);
		FVector M1 = FMath::Lerp(P1, P2, i);
		FVector B = FMath::Lerp(M0, M1, i);

		LinePositions.Add(B);
	}

	return LinePositions;
}
