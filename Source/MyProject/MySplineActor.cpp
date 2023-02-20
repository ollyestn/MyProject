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

	ForwardAxis = ESplineMeshAxis::Type::Z;
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
        pSplineMesh->SetForwardAxis(ForwardAxis);
        FVector UpDir(1, 0, 0);
        pSplineMesh->SetSplineUpDir(UpDir);
        FVector StartPos;
        FVector StartTangent;
        Spline->GetLocationAndTangentAtSplinePoint(i, StartPos, StartTangent, ESplineCoordinateSpace::Local);
        //Spline->SetSplinePointType(i, ESplinePointType::Type::Linear);
        FVector EndPos;
        FVector EndTangent;
        Spline->GetLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent, ESplineCoordinateSpace::Local);
        pSplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
    }

    //注册组件
    RegisterAllComponents();
}

void AMySplineActor::SetSplinePoints(const TArray<FVector>& SplinePoints)
{
    Spline->SetSplineLocalPoints(SplinePoints);
}


void AMySplineActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    //if (PropertyChangedEvent.Property != nullptr) 
    // {
    //    const FName PropertyName = PropertyChangedEvent.Property->GetFName();   //获得该类所有属性的名字

    //    //const FString PropertyName = PropertyChangedEvent.Property->GetName();
    //    //PropertyName == GET_MEMBER_NAME_STRING_CHECKED(AHost,show)

    //    if (PropertyName == GET_MEMBER_NAME_CHECKED(AHost, show)) {   //当这个属性名字属于AHost类,且属性名字为show时候，myMesh改变visibility。
    //        myMesh->SetVisibility(show);
    //    }
    //}
    //Super::PostEditChangeProperty(PropertyChangedEvent); //调用父类的PostEditChangeProperty方法。

    //Spline->UpdateSpline();
}