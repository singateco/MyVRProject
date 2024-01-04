// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCar.generated.h"

UCLASS()
class MYVRPROJECT_API AMyCar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCar();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void RotateCar(const float Angle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
