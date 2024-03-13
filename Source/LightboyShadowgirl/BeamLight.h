// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Light2D.h"
#include "LightInterface.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "BeamLight.generated.h"

UCLASS()
class LIGHTBOYSHADOWGIRL_API ABeamLight : public ALight2D, public ILightInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BeamWidth;
	
	ABeamLight();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	virtual void UpdateMesh() const override;
	virtual bool Reaches_Implementation(FVector Point) const override;
};
