#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Materials/MaterialExpressionCustomOutput.h"
#include "MaterialExpressionPreintegratedSkinMaterialOutput.generated.h"

UCLASS(MinimalAPI, collapsecategories, hidecategories = Object)
class UMaterialExpressionPreintegratedSkinMaterialOutput : public UMaterialExpressionCustomOutput
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	FExpressionInput Curvature;

	UPROPERTY()
	FExpressionInput CurvatureTensor;

	UPROPERTY()
	FExpressionInput NormalScale;

	UPROPERTY()
	FExpressionInput FalloffColor;

	UPROPERTY()
	FExpressionInput ScatterColor;

public:
#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;
#endif

	virtual int32 GetNumOutputs() const override;
	virtual FString GetFunctionName() const override;
	virtual FString GetDisplayName() const override;
};
