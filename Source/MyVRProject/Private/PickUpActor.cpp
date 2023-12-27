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

void APickUpActor::Grabbed(USkeletalMeshComponent* HandMesh, EAttachmentRule AttachmentRules)
{
	// 부착되기전 물리 끄기
	BoxComponent->SetEnableGravity(false);
	BoxComponent->SetSimulatePhysics(false);

	// 잡혔을 때의 핸드 메시에 부착된다.

	if (AttachmentRules == EAttachmentRule::KeepWorld)
	{
		const FAttachmentTransformRules Rules = FAttachmentTransformRules::KeepWorldTransform;
		// 잡는 순간의 간격을 유지하면서 붙인다
		this->AttachToComponent(HandMesh, Rules);
	}
	else if (AttachmentRules == EAttachmentRule::SnapToTarget)
	{
		const FAttachmentTransformRules Rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

		// 지정된 위치로 이동해서 붙인다
		this->AttachToComponent(HandMesh, Rules, FName("GrabSocket"));

		// 오프셋 적용
		SetActorRelativeLocation(LocationOffset);
	}
}

void APickUpActor::Released(FVector DeltaPosition, FQuat DeltaRotation)
{
	BoxComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetEnableGravity(true);

	// 임계값 넘으면 Released된 액터에 힘 가하기
	if (DeltaPosition.Size() > 0.05f)
	{
		BoxComponent->AddImpulse(DeltaPosition * ThrowPower);
		BoxComponent->AddTorqueInRadians(DeltaRotation.GetRotationAxis() * RotPower);
	}
	
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

