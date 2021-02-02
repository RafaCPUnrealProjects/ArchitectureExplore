// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HandController.h"
#include "VRCharacter.generated.h"

UCLASS()
class ARCHITECTUREEXPLORE_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateDestinationMarker();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float throttle);

	void MoveRight(float throttle);

	void BeginTeleport();
	void FinishTeleport();

	void UpdateBlinkers();
	FVector2D GetBlinkerCenter();

	UPROPERTY(EditAnywhere)
	float MaxTeletportDistance = 1000.0f;
	
	UPROPERTY(EditAnywhere)
	float TeleportFadeTime = 2.0f;
	
	UPROPERTY(EditAnywhere)
	FVector TeleportProjectionExtent = FVector(100,100,100);

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DestinationMarker;

	UPROPERTY()
	class UPostProcessComponent* PostProcessComponent;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* BlinkerMaterialBase;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* BlinkerMaterialInstance;

	UPROPERTY(EditAnywhere)
	class UCurveFloat* RadiusVsVelocity;

	UPROPERTY(VisibleAnywhere)
	class AHandController* RightController;

	UPROPERTY(VisibleAnywhere)
	class AHandController* LeftController;
	
	UPROPERTY(VisibleAnywhere)
	class USplineComponent* TeleportPath;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMesh* TeleportArchMesh;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* TeleportArchMaterial;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHandController> HandController;

	UPROPERTY()
	TArray<class USplineMeshComponent*> TeleportPathMeshPool;

	void GripLeft(){LeftController->Grip();}
	void ReleaseLeft() { LeftController->Release(); }
	void GripRight() { RightController->Grip(); }
	void ReleaseRight() { RightController->Release(); }
};
