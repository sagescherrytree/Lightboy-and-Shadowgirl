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
	float DeltaWidth = BeamWidth / (NumRays - 1);
 
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
 
	for (int32 i = 0; i < NumRays; i++)
	{
		const float Displacement = DeltaWidth * i - 0.5f * BeamWidth;
		const FVector Start = FVector(0.f, 0.f, Displacement);
		Vertices.Add(Start);
		const FVector End = Start + RayLength * FVector::ForwardVector;
		const FVector HitPos = RayCast(Start, End);
		Vertices.Add(HitPos);
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
	const FTransform Transform = GetActorTransform();
	const FVector LocalPoint = Transform.InverseTransformPosition(Point);
	if (std::abs(LocalPoint.Z) > BeamWidth / 2.f)
	{
		return false;
	}
	const FVector Start = Transform.TransformPosition(FVector(0.f, 0.f, LocalPoint.Z));
	return RayReaches(Start, Point);
}