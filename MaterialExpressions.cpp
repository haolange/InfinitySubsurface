///////////////////////////////////////////////////////////////////////////////
// UMaterialExpressionPreintegratedSkinMaterialOutput
///////////////////////////////////////////////////////////////////////////////
UMaterialExpressionPreintegratedSkinMaterialOutput::UMaterialExpressionPreintegratedSkinMaterialOutput(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	struct FConstructorStatics
	{
		FText NAME_Skin;
		FConstructorStatics() : NAME_Skin(LOCTEXT("Skin", "Skin"))
		{

		}
	};
	static FConstructorStatics ConstructorStatics;

#if WITH_EDITORONLY_DATA
	MenuCategories.Add(ConstructorStatics.NAME_Skin);
#endif

#if WITH_EDITOR
	Outputs.Reset();
#endif
}

#if WITH_EDITOR

int32 UMaterialExpressionPreintegratedSkinMaterialOutput::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
	int32 CodeInput = INDEX_NONE;

	if (!Curvature.IsConnected() && !CurvatureTensor.IsConnected()  && !NormalScale.IsConnected() && !ScatterColor.IsConnected() && !FalloffColor.IsConnected())
	{
		Compiler->Error(TEXT("No inputs to Preintegrated Skin Material."));
	}

	if (OutputIndex == 0)
	{
		CodeInput = Curvature.IsConnected() ? Curvature.Compile(Compiler) : Compiler->Constant(0.1);
	}
	else if (OutputIndex == 1)
	{
		CodeInput = CurvatureTensor.IsConnected() ? CurvatureTensor.Compile(Compiler) : Compiler->Constant3(1.0, 1.0, 1.0);
	}
	else if (OutputIndex == 2)
	{
		CodeInput = NormalScale.IsConnected() ? NormalScale.Compile(Compiler) : Compiler->Constant(1.0);
	}
	else if (OutputIndex == 3)
	{
		CodeInput = FalloffColor.IsConnected() ? FalloffColor.Compile(Compiler) : Compiler->Constant3(0.88, 0.65, 0.25);
	}
	else if (OutputIndex == 4)
	{
		CodeInput = ScatterColor.IsConnected() ? ScatterColor.Compile(Compiler) : Compiler->Constant3(1.0, 0.2, 0.1);
	}
	return Compiler->CustomOutput(this, OutputIndex, CodeInput);
}

void UMaterialExpressionPreintegratedSkinMaterialOutput::GetCaption(TArray<FString>& OutCaptions) const
{
	OutCaptions.Add(FString(TEXT("Preintegrated Skin Material")));
}

#endif // WITH_EDITOR

int32 UMaterialExpressionPreintegratedSkinMaterialOutput::GetNumOutputs() const
{
	return 5;
}

FString UMaterialExpressionPreintegratedSkinMaterialOutput::GetFunctionName() const
{
	return TEXT("GetPreintegratedSkinMaterialOutput");
}

FString UMaterialExpressionPreintegratedSkinMaterialOutput::GetDisplayName() const
{
	return TEXT("Preintegrated Skin Material");
}

///////////////////////////////////////////////////////////////////////////////
// UMaterialExpressionObjectBoundingBox
///////////////////////////////////////////////////////////////////////////////