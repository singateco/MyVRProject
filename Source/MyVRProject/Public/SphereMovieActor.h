// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereMovieActor.generated.h"

UCLASS()
class MYVRPROJECT_API ASphereMovieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereMovieActor();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class USceneComponent* RootComp;
	
	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	class UMediaSoundComponent* SoundComp;

	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	class UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	class UMediaSource* MediaSource;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
