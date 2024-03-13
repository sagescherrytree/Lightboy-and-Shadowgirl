// Fill out your copyright notice in the Description page of Project Settings.


#include "Light2D.h"

// Sets default values
ALight2D::ALight2D()
{
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	const TArray<FVector> Vertices;
	const TArray<int32> Triangles;
	WriteMesh(Vertices, Triangles);
	PrimaryActorTick.bCanEverTick = true;
}

void ALight2D::WriteMesh(const TArray<FVector>& Vertices, const TArray<int32>& Triangles) const
{
	const TArray<FVector> Normals;
	const TArray<FVector2D> UVs;
	const TArray<FColor> VertexColors;
	Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, TArray<FProcMeshTangent>(), false);
}

FVector ALight2D::RayCast(FVector Start, FVector End, bool& bHit) const
{
	const FTransform Transform = GetActorTransform();
	Start = Transform.TransformPosition(Start);
	End = Transform.TransformPosition(End);
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
	return bHit ? Transform.InverseTransformPosition(HitResult.Location) : End;
}

// Called when the game starts or when spawned
void ALight2D::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALight2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

