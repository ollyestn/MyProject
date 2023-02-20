// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform);

	USplineComponent* GenerateSplineComponent(TArray< FVector> posArray, AActor* actor);
	void GenerateSplineMeshComponentFromSplineComponent(AActor* parentActor, USplineComponent* splineComponent);

public:
	//线条使用的静态mesh
	UPROPERTY(EditAnywhere, Category = "Spline", meta = (AllowPrivateAccess = true))
		class UStaticMesh* SplineStaticMesh;

public:
	UFUNCTION(BlueprintCallable, Category = "SpatialGrid,BlueprintFunc")
		void CreateSpline();

	UFUNCTION(BlueprintCallable, Category = "Spline")
		void CreateSplineActor();
};
