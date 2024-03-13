// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Light2D.generated.h"

UCLASS()
class LIGHTBOYSHADOWGIRL_API ALight2D : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProceduralMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumRays;

	static constexpr float RayLength = 1000.f;
	
	// Sets default values for this actor's properties
	ALight2D();

protected:
	void WriteMesh(const TArray<FVector>& Vertices, const TArray<int32>& Triangles) const;
	bool RayCast(FHitResult& HitResult, const FVector& Start, const FVector& End) const;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
