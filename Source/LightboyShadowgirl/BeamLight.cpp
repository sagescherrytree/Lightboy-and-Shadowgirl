// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamLight.h"

// Sets default values
ABeamLight::ABeamLight() : ALight2D()
{
}

// Called when the game starts or when spawned
void ABeamLight::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABeamLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMesh();
}

void ABeamLight::UpdateMesh() const
{
	const FTransform Transform = Mesh->GetComponentTransform();
	
	float DeltaWidth = BeamWidth / (NumRays - 1);
 
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
 
	for (int32 i = 0; i < NumRays; i++)
	{
		const float Displacement = DeltaWidth * i - 0.5f * BeamWidth;
		const FVector LocalStart = FVector(0.f, 0.f, Displacement);
		Vertices.Add(LocalStart);
		const FVector Start = Transform.TransformPosition(LocalStart);
		const FVector End = Transform.TransformPosition(LocalStart + RayLength * FVector::ForwardVector);
		
		FHitResult HitResult;
		bool bHit = RayCast(HitResult, Start, End);
 
		const FVector WorldHitPos = bHit ? HitResult.Location : End;
		const FVector LocalHitPos = Transform.InverseTransformPosition(WorldHitPos);
		Vertices.Add(LocalHitPos);
	}

	for (int32 i = 0; i < 2 * NumRays - 2; i += 2)
	{
		Triangles.Append({i, i + 1, i + 2, i + 1, i + 3, i + 2});
	}
 
	Vertices.Add(FVector::ZeroVector);
	WriteMesh(Vertices, Triangles);
}

bool ABeamLight::Reaches_Implementation(FVector Point) const
{
	return true;
}