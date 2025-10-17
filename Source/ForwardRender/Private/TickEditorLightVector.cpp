// Copyright (c) Jared Taylor


#include "TickEditorLightVector.h"

#include "EngineUtils.h"
#include "ForwardRenderSettings.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TickEditorLightVector)

void UTickEditorLightVector::Tick(float DeltaTime)
{
	const UForwardRenderSettings* Settings = GetDefault<UForwardRenderSettings>();
	
	if (!Settings->bLightVectorEnabled)
	{
		return;
	}
	
	if (!GEditor)
	{
		return;
	}

	const UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World || World->WorldType != EWorldType::Editor)
	{
		return;
	}

	const ADirectionalLight* DirectionalLight = nullptr;
	int32 NumLights = 0;
	for (TActorIterator<ADirectionalLight> It(World); It; ++It)
	{
		if (!DirectionalLight)
		{
			DirectionalLight = *It;
			if (!Settings->bWarnOnMultipleDirectionalLights)
			{
				break;
			}
		}
		NumLights++;
	}

	if (!DirectionalLight)
	{
		return;
	}

	if (Settings->bWarnOnMultipleDirectionalLights && !bHasWarned && NumLights > 1)
	{
		bHasWarned = true;
		
		FMessageLog("TickEditorLightVector").Warning()
			->AddToken(FTextToken::Create(FText::FromString(TEXT("Multiple Directional Lights found in the scene. TickEditorLightVector will only use the first one found."))))
			->AddToken(FTextToken::Create(FText::FromString(World->GetMapName())));
	}

	const FVector LightDirWS = DirectionalLight->GetLightComponent()->GetForwardVector();

	const UMaterialParameterCollection* MPC = Cast<UMaterialParameterCollection>(Settings->LightVectorMPCPath.TryLoad());
	if (!MPC)
	{
		return;
	}

	UMaterialParameterCollectionInstance* Instance = World->GetParameterCollectionInstance(MPC);
	if (Instance)
	{
		Instance->SetVectorParameterValue(Settings->LightVectorParameterName, FLinearColor(Settings->bInvertLightVector ? -LightDirWS : LightDirWS));
	}
}

bool UTickEditorLightVector::IsTickable() const
{
	return GetDefault<UForwardRenderSettings>()->bLightVectorEnabled;
}
