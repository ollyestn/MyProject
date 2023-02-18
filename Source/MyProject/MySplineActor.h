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

    //�������
    UPROPERTY(VisibleDefaultsOnly, Category = "Spline", meta = (AllowPrivateAccess = true))
        class USplineComponent* Spline;

    //����ʹ�õľ�̬mesh
    UPROPERTY(EditAnywhere, Category = "Spline", meta = (AllowPrivateAccess = true))
        class UStaticMesh* SplineStaticMesh;

    //Mesh�ĳ���
    UPROPERTY(EditAnywhere, Category = "Spline", meta = (AllowPrivateAccess = true))
        TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

private:

    //��������Mesh
    void CreateSplineMesh();


public:

    //����Spline�Ķ���
    void SetSplinePoints(const TArray<FVector>& SplinePoints);
};
