// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

UCLASS()
class MYVRPROJECT_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	APickUpActor();

	UPROPERTY(EditAnywhere, Category = "MySettings|Component")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "MySettings|Component")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "MySettings|Values")
	FVector LocationOffset = FVector(0, 0, 10);

	UPROPERTY(EditAnywhere, Category = "MySettings|Values")
	float ThrowPower { 500 };

	UPROPERTY(EditAnywhere, Category = "MySettings|Values")
	float RotPower { 50 };

	void Grabbed(class USkeletalMeshComponent* HandMesh, EAttachmentRule AttachmentRules);

	void Released(FVector DeltaPosition, FQuat DeltaRotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
