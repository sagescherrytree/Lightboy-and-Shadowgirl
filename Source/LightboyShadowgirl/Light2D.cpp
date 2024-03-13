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

FVector ALight2D::RayCast(FVector LocalStart, FVector LocalEnd) const
{
	const FTransform Transform = GetActorTransform();
	// Convert to global space
	LocalStart = Transform.TransformPosition(LocalStart);
	LocalEnd = Transform.TransformPosition(LocalEnd);
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, LocalStart, LocalEnd, ECC_GameTraceChannel1, CollisionParams);
	return Transform.InverseTransformPosition(bHit ? HitResult.Location : LocalEnd);
}

bool ALight2D::RayReaches(FVector GlobalStart, FVector GlobalEnd) const
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	return !GetWorld()->LineTraceSingleByChannel(HitResult, GlobalStart, GlobalEnd, ECC_GameTraceChannel1, CollisionParams);
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

