// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportRingActor.h"

#include "NiagaraComponent.h"

// Sets default values
ATeleportRingActor::ATeleportRingActor()
	:
	RingFX(CreateDefaultSubobject<UNiagaraComponent>(TEXT("Ring FX")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RingFX->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATeleportRingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportRingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

