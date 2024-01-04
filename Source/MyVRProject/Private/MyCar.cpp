// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyCar::AMyCar()
	:
	BoxComp(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"))),
	MeshComp(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetWorldScale3D(FVector(2, 0.8f, 1.0f));

	MeshComp->SetupAttachment(BoxComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyCar::RotateCar(const float Angle)
{
	//SetActorRotation(GetActorRotation() + FRotator(0, Angle, 0));

	SetActorRotation(FRotator(0, Angle, 0));
}

// Called when the game starts or when spawned
void AMyCar::BeginPlay()
{
	Super::BeginPlay();

}