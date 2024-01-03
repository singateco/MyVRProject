// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereMovieActor.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"

// Sets default values
ASphereMovieActor::ASphereMovieActor()
	:
	RootComp(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"))),
	MeshComp(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"))),
	SoundComp(CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Sound Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(RootComp);
	RootComp->SetWorldScale3D(FVector(3.f));

	MeshComp->SetupAttachment(RootComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SoundComp->SetupAttachment(RootComp);

	if (nullptr != MediaPlayer)
	{
		SoundComp->SetMediaPlayer(MediaPlayer);
	}
}

// Called when the game starts or when spawned
void ASphereMovieActor::BeginPlay()
{
	Super::BeginPlay();

	if (MediaSource && MediaPlayer)
	{
		MediaPlayer->OpenSource(MediaSource);
		//SoundComp->Activate(true);
		//SoundComp->SetVolumeMultiplier(2.f);
	}
}

// Called every frame
void ASphereMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

