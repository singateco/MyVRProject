// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKeyboardActor::AKeyboardActor()
	:
	BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"))),
	MeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionObjectType(ECC_GameTraceChannel3);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);

	BoxComponent->SetBoxExtent(FVector(50));
	BoxComponent->SetWorldScale3D(FVector(0.2f, 0.05f, 0.05f));

	MeshComponent->SetupAttachment(BoxComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetRelativeLocation(FVector(0, 0, -50));
}

void AKeyboardActor::ResetKeyColor()
{
	KeyMat->SetVectorParameterValue(FName("EmissiveColor"), FVector4(1.0f, 1.0f, 1.0f, 1.0f));
	KeyMat->SetScalarParameterValue(FName("Intensity"), 1.f);
}

// Called when the game starts or when spawned
void AKeyboardActor::BeginPlay()
{
	Super::BeginPlay();

	// Box Component에 충돌 이벤트 함수 바인드하기
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKeyboardActor::OnHitKey);

	KeyMat = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), nullptr);
	MeshComponent->SetMaterial(0, KeyMat);
}

// Called every frame
void AKeyboardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AKeyboardActor::OnHitKey(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), KeySound, GetActorLocation(), GetActorRotation());

	KeyMat->SetVectorParameterValue(FName("EmissiveColor"), FVector4(0.276877, 0.958333, 0.297632, 1.000000));
	KeyMat->SetScalarParameterValue(FName("Intensity"), 5.f);

	FTimerHandle ResetHandle;
	GetWorld()->GetTimerManager().ClearTimer(ResetHandle);
	GetWorld()->GetTimerManager().SetTimer(ResetHandle, this, &AKeyboardActor::ResetKeyColor, 0.5f, false);
}



