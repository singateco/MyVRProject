// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportRingActor.generated.h"

UCLASS()
class MYVRPROJECT_API ATeleportRingActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	ATeleportRingActor();

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UNiagaraComponent* RingFX;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
