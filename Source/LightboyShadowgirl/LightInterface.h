#pragma once

#include "LightInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class ULightInterface : public UInterface
{
	GENERATED_BODY()
};

class ILightInterface
{
	GENERATED_BODY()

public:
	virtual void UpdateMesh() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LightInterface")
	bool Reaches(FVector Point) const;
};
