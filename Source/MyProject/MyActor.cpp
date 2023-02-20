// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "MySplineActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 第一种方式
void AMyActor::CreateSpline()
{
	TArray<FVector> posArray;
	FVector v1 = FVector(0, 0,100);
	FVector v2 = FVector(1000, 0, 100);
	FVector v3 = FVector(1000, 1000, 100);
	posArray.Add(v1);posArray.Add(v2);posArray.Add(v3);

	USplineComponent* splineComponent = this->GenerateSplineComponent(posArray, this);
	splineComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

USplineComponent* AMyActor::GenerateSplineComponent(TArray< FVector> posArray, AActor* actor)
{
	USplineComponent* splineTrack = NewObject<USplineComponent>(actor, TEXT("Spline"));
	splineTrack->RegisterComponent();

	//设置样本条的颜色
	splineTrack->SetUnselectedSplineSegmentColor(FLinearColor(0.0f, 0.0f, 1.0f));
	//设置样条线的粗细或者宽度
	splineTrack->ScaleVisualizationWidth = 70.0f;
	splineTrack->SetSplineLocalPoints(posArray);
	splineTrack->SetDrawDebug(true);
	splineTrack->UpdateSpline();
	splineTrack->SetHiddenInGame(false);

	return splineTrack;
}

// 第三种方式
//void MyActor::GenerateSplineMeshComponentFromSplineComponent(AActor* parentActor, USplineComponent* splineComponent)
//{
//	if (nullptr == splineComponent)
//		return;
//	
//	for (int i = 0; i < splineComponent->GetNumberOfSplinePoints() - 1; i++)
//	{
//		USplineMeshComponent* splineMesh = NewObject< USplineMeshComponent>(parentActor, TEXT(“SplineMesh” + i));
//		splineMesh->RegisterComponent();
//		splineMesh->AttachToComponent(parentActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//		splineMesh->SetStaticMesh(_splineStaticMesh);
//
//		splineMesh->SetMobility(EComponentMobility::Type::Movable);
//		FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
//		splineComponent->GetLocalLocationAndTangentAtSplinePoint(i, pointLocationStart, pointTangentStart);
//		splineComponent->GetLocalLocationAndTangentAtSplinePoint(i + 1, pointLocationEnd, pointTangentEnd);
//
//		splineMesh->SetStartAndEnd(pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd);
//	}
//}

//[UE4]C++代码操作SplineMesh
void AMyActor::OnConstruction(const FTransform& Transform)
{
	//for (int32 i = 0; i < mSplineComponent->GetNumSplinePoints() - 1; i++)
	//{
	//	USplineMeshComponent* SplineMesh = ConstructObject<USplineMeshComponent>(USplineMeshComponent::StaticClass(), this);

	//	SplineMesh->bCreatedByConstructionScript = true;
	//	SplineMesh->SetMobility(EComponentMobility::Movable);
	//	SplineMesh->AttachParent = mSplineComponent;

	//	//Set the color!
	//	UMaterialInstanceDynamic* dynamicMat = UMaterialInstanceDynamic::Create(mSplineMeshMaterial, NULL);
	//	dynamicMat->SetVectorParameterValue(TEXT("Color"), FLinearColor(mSegments[i].mColor));

	//	SplineMesh->bCastDynamicShadow = false;
	//	SplineMesh->SetStaticMesh(mGridMesh);
	//	SplineMesh->SetMaterial(0, dynamicMat);

	//	//Width of the mesh 
	//	SplineMesh->SetStartScale(FVector2D(50, 50));
	//	SplineMesh->SetEndScale(FVector2D(50, 50));

	//	FVector pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd;
	//	mSplineComponent->GetLocalLocationAndTangentAtSplinePoint(i, pointLocationStart, pointTangentStart);
	//	mSplineComponent->GetLocalLocationAndTangentAtSplinePoint(i + 1, pointLocationEnd, pointTangentEnd);

	//	SplineMesh->SetStartAndEnd(pointLocationStart, pointTangentStart, pointLocationEnd, pointTangentEnd);
	//}

	//RegisterAllComponents();

	CreateSplineActor();
}

// 创建 AMySplineActor
void AMyActor::CreateSplineActor()
{
	FVector WallLocation(0, 0, 0);
	FVector Location = WallLocation;
	FRotator Rotation(0.f, 0.f, 0.f);
	FVector Scale(1.f, 1.f, 1.f);
	FTransform SpawnTransform = FTransform(Rotation, Location, Scale);

	TArray<FVector> WallPointList;

	FVector v1 = FVector(0, 0, 0);
	FVector v2 = FVector(0, 0, 1000);
	FVector v3 = FVector(0, 0, 2000);
	WallPointList.Add(v1); WallPointList.Add(v2); WallPointList.Add(v3);

	AMySplineActor* pSplineActor = GetWorld()->SpawnActorDeferred<AMySplineActor>(AMySplineActor::StaticClass(), SpawnTransform); //SplineClass
	if (pSplineActor)
	{
		pSplineActor->SetSplinePoints(WallPointList);
		pSplineActor->SplineStaticMesh = SplineStaticMesh;
		UGameplayStatics::FinishSpawningActor(pSplineActor, SpawnTransform);		
	}
}
