// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "HandController.generated.h"

UCLASS()
class ARCHITECTUREEXPLORE_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* MotionController;

	UFUNCTION()
	void ActorBeingOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly)
	class UHapticFeedbackEffect_Base* HapticEffect;

	bool bCanClimb = false;

	bool CanClimb() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); }

	void Grip();

	void Release();

	bool bIsClimbing = false;
	FVector ClimbingStartLocation;

	void PairController(AHandController* Controller);

	AHandController* OtherController;
};
