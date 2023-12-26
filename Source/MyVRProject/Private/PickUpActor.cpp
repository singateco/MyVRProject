// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"

#include "Components/BoxComponent.h"

// Sets default values
APickUpActor::APickUpActor()
	:
	BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"))),
	MeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(BoxComponent);
	MeshComponent->SetupAttachment(RootComponent);

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionProfileName(FName("PickUpPreset"));

	// 물리 사용
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetEnableGravity(true);

	// 크기 설정
	BoxComponent->SetWorldScale3D(FVector(0.1f, 0.1f, 0.3f));
	BoxComponent->SetBoxExtent(FVector(50));

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

