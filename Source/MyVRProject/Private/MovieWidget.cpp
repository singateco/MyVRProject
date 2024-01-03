// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieWidget.h"

#include "WideMovieActor.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UMovieWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Back->OnClicked.AddDynamic(this, &UMovieWidget::Back10Seconds);
	Btn_Stop->OnClicked.AddDynamic(this, &UMovieWidget::StopMovie);
	Btn_Play->OnClicked.AddDynamic(this, &UMovieWidget::PlayMovie);
	Btn_Forward->OnClicked.AddDynamic(this, &UMovieWidget::Forward10Seconds);
}

void UMovieWidget::Back10Seconds()
{
	MovieActor->Back();
}

void UMovieWidget::StopMovie()
{
	MovieActor->Stop();
}

void UMovieWidget::PlayMovie()
{
	MovieActor->Play();
}

void UMovieWidget::Forward10Seconds()
{
	MovieActor->Forward();
}
