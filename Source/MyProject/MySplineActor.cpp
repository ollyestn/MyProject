// Fill out your copyright notice in the Description page of Project Settings.


#include "MySplineActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AMySplineActor::AMySplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent0"));
	RootComponent = (USceneComponent*)Spline;

	ForwardAxis = ESplineMeshAxis::Type::X;
}

void AMySplineActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateSplineMesh();
}

// Called when the game starts or when spawned
void AMySplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMySplineActor::CreateSplineMesh()
{
    if (Spline->GetNumberOfSplinePoints() < 2)
        return;

    for (int32 i = 0; i < Spline->GetNumberOfSplinePoints() - 1; i++)
    {
        USplineMeshComponent* pSplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
        pSplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
        pSplineMesh->SetStaticMesh(SplineStaticMesh);
        pSplineMesh->SetupAttachment(Spline);
        pSplineMesh->SetForwardAxis(ForwardAxis, false);
        FVector StartPos;
        FVector StartTangent;
        Spline->GetLocationAndTangentAtSplinePoint(i, StartPos, StartTangent, ESplineCoordinateSpace::Local);
        FVector EndPos;
        FVector EndTangent;
        Spline->GetLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent, ESplineCoordinateSpace::Local);
        pSplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
    }

    //×¢²á×é¼þ
    RegisterAllComponents();
}

void AMySplineActor::SetSplinePoints(const TArray<FVector>& SplinePoints)
{
    Spline->SetSplineLocalPoints(SplinePoints);
}


