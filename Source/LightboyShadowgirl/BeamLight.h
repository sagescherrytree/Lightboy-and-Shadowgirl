// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightInterface.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "BeamLight.generated.h"

UCLASS()
class LIGHTBOYSHADOWGIRL_API ABeamLight : public AActor, public ILightInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProceduralMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumRays;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BeamWidth;
	
	ABeamLight();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	virtual void UpdateMesh() const override;
	virtual bool Reaches(FVector Point) const override;
	
};
