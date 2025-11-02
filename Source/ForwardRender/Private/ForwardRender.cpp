// Copyright (c) Jared Taylor

#include "ForwardRender.h"

#define LOCTEXT_NAMESPACE "FForwardRenderModule"

void FForwardRenderModule::StartupModule()
{
	// Hook to map changes to toggle back to the mobile preview.
	FEditorDelegates::MapChange.AddRaw(this, &FForwardRenderModule::OnMapChange);

	// Hotpatch Engine/Config/Windows/DataDrivenPlatformInfo.ini, we find section
	// [ShaderPlatform PCD3D_ES3_1] and then look for bSupportsDistanceFields = false
	// and patch the value onto true, otherwise our lighting will be black due to no mobile DF support.
	const FString IniPath = FPaths::Combine(FPaths::EngineDir(), TEXT("Config/Windows/DataDrivenPlatformInfo.ini"));
	FString FileContent;

	if (FPaths::FileExists(IniPath) && FFileHelper::LoadFileToString(FileContent, *IniPath))
	{
		const FString SectionHeader = TEXT("[ShaderPlatform PCD3D_ES3_1]");
		const FString Key = TEXT("bSupportsDistanceFields");
		const FString OldLine = Key + TEXT(" = false");
		const FString NewLine = Key + TEXT(" = true");

		const int32 SectionStart = FileContent.Find(SectionHeader, ESearchCase::IgnoreCase);
		if (SectionStart != INDEX_NONE)
		{
			const int32 KeyStart = FileContent.Find(OldLine, ESearchCase::IgnoreCase, ESearchDir::FromStart, SectionStart);
			if (KeyStart != INDEX_NONE)
			{
				FileContent = FileContent.Replace(*OldLine, *NewLine, ESearchCase::IgnoreCase);
				FFileHelper::SaveStringToFile(FileContent, *IniPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
			}
		}
	}
}

void FForwardRenderModule::ShutdownModule()
{
	FEditorDelegates::MapChange.RemoveAll(this);
}

void FForwardRenderModule::OnMapChange(uint32)
{
#if PLATFORM_WINDOWS
	// Force the editor into DirectX Mobile Preview on ES31
	// Stole these settings from Engine/Config/Windows/DataDrivenPlatformInfo.ini
	const FPreviewPlatformInfo PreviewPlatform(
		ERHIFeatureLevel::ES3_1,
		SP_PCD3D_ES3_1,
		FName("PC"),
		FName("PCD3D_ES31"),
		FName("Windows_Preview_ES31"),
		true,
		FName("PCD3D_ES3_1_Preview")
		);


	GEditor->SetPreviewPlatform(PreviewPlatform, false);
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FForwardRenderModule, ForwardRender)