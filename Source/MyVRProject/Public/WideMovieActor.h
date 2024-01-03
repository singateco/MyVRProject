// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WideMovieActor.generated.h"

UCLASS()
class MYVRPROJECT_API AWideMovieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWideMovieActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySttings")
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, Category = "MySttings")
	class UWidgetComponent* MovieWidget;

	UPROPERTY(EditAnywhere, Category = "MySttings")
	class UMediaSource* MovieSource;

	UPROPERTY(EditAnywhere, Category = "MySttings")
	class UMediaPlayer* MoviePlayer;

	void Back();
	void Stop();
	void Play();
	void Forward();
};
