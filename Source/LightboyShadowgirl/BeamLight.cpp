// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamLight.h"

// Sets default values
ABeamLight::ABeamLight()
{
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = Mesh;
	
	const TArray<FVector> Vertices;
	const TArray<int32> Triangles;
	const TArray<FVector> Normals;
	const TArray<FVector2D> UVs;
	const TArray<FColor> VertexColors;
	Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, TArray<FProcMeshTangent>(), false);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABeamLight::BeginPlay()
{
	Super::BeginPlay();
	UpdateMesh();
}

// Called every frame
void ABeamLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABeamLight::UpdateMesh() const
{
	Mesh->ClearMeshSection(0);
	
	const FTransform Transform = Mesh->GetComponentTransform();
	
	float DeltaWidth = BeamWidth / (NumRays - 1);
	constexpr float RayLength = 1000.f;
 
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
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
 
		const FVector WorldHitPos = bHit ? HitResult.Location : End;
		const FVector LocalHitPos = Transform.InverseTransformPosition(WorldHitPos);
		Vertices.Add(LocalHitPos);
	}

	for (auto vert : Vertices)
	{
		UE_LOG(LogTemp, Log, TEXT("v: %s"), *vert.ToString());
	}

	for (int32 i = 0; i < 2 * NumRays; i += 2)
	{
		Triangles.Append({i, i + 1, i + 2, i + 1, i + 3, i + 2});
	}
 
	Vertices.Add(FVector::ZeroVector);
	
	const TArray<FVector> Normals;
	const TArray<FVector2D> UV0;
	const TArray<FProcMeshTangent> Tangents;
	const TArray<FLinearColor> VertexColors;
	Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, false);
}

bool ABeamLight::Reaches(FVector Point) const
{
	return true;
}