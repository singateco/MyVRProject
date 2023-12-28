// Fill out your copyright notice in the Description page of Project Settings.


#include "PianoActor.h"

#include "KeyboardActor.h"
#include "Components/ChildActorComponent.h"

// Sets default values
APianoActor::APianoActor()
	:
	RootComp(CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(RootComp);

	// 위치 설정값 구하기
	constexpr float Width = (5 * 8) + (3 * (8 - 1));
	const FVector StartLoc = FVector(0, Width * 0.5f * -1 + 2.5f, 0);

	for (int32 i = 0; i < 8; i++)
	{
		// 이름 짓기
		FString ActorName = FString::Printf(TEXT("Keyboard_%d"), i);

		// 자식 액터를 만든다
		UChildActorComponent* Child = CreateDefaultSubobject<UChildActorComponent>(FName(*ActorName));

		// 자식 액터를 루트에 붙이기
		Child->SetupAttachment(RootComp);

		// 배열에 저장
		KeyActors.Add(Child);

		// 위치 설정
		Child->SetRelativeLocation(StartLoc + FVector(0, 8 * i, 0));
	}
}

// Called when the game starts or when spawned
void APianoActor::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < KeySounds.Num(); i++)
	{
		// 키보드 액터마다 Keysound 변수에 음원 파일들을 넣어준다.
		if (nullptr != KeyActors[i]->GetChildActor())
		{
			Cast<AKeyboardActor>(KeyActors[i]->GetChildActor())->KeySound = KeySounds[i];
		}

	}
}

// Called every frame
void APianoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

