// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "MySplineActor.generated.h"

UCLASS()
class MYPROJECT_API AMySplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySplineActor();

protected:

	virtual void OnConstruction(const FTransform& Transform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

    //线条组件
    UPROPERTY(VisibleDefaultsOnly, Category = "Spline", meta = (AllowPrivateAccess = true))
        class USplineComponent* Spline;

    //线条使用的静态mesh
    UPROPERTY(EditAnywhere, Category = "Spline", meta = (AllowPrivateAccess = true))
        class UStaticMesh* SplineStaticMesh;

    //Mesh的朝向
    UPROPERTY(EditAnywhere, Category = "Spline", meta = (AllowPrivateAccess = true))
        TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

private:

    //生成线条Mesh
    void CreateSplineMesh();


public:

    //设置Spline的顶点
    void SetSplinePoints(const TArray<FVector>& SplinePoints);
};
