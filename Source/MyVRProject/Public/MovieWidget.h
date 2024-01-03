// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MovieWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UMovieWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="MySettings", meta = (BindWidget))
	class UImage* Screen;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UButton* Btn_Back;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	UButton* Btn_Stop;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	UButton* Btn_Play;

	UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	UButton* Btn_Forward;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class AWideMovieActor* MovieActor;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void Back10Seconds();

	UFUNCTION()
	void StopMovie();

	UFUNCTION()
	void PlayMovie();

	UFUNCTION()
	void Forward10Seconds();
};
